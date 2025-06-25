-module(sv).
-export([recibir/0, enviar/3]).

-define(PORT, 8080).

recibir() ->
	{ok, Lsock} = gen_tcp:listen(?PORT, [binary, {packet, 0}, {active, false}, {reuseaddr, true}]),
	io:format("Esperando conexion en ~p~n", [?PORT]),
	{ok, Sock} = gen_tcp:accept(Lsock),
	io:format("Conexion aceptada~n"),
	recibir_archivo(Sock),
	gen_tcp:close(Sock),
	gen_tco:close(Lsock).

recibir_archivo(Sock) -> 
	case gen_tcp:recv(Sock,0) of
		{ok, Bin} ->
			file:write_file("archivo_recibido", Bin),
			io:format("Archivo recibido.~n");
		{error, Reason} ->
			io:format("Error al recibir : ~p~n", [Reason])
	end.

enviar(IP, Puerto, RutaArchivo) ->
	{ok,Bin} = file:read_file(RutaArchivo),
	{ok,Sock} = gen_tcp:connect(IP, Puerto, [binary, {packet, 0}, {active, false}]),
	ok = gen_tcp:send(Sock,Bin),
	io:format("Archivo enviado~n"),
	gen_tcp:close(Sock).