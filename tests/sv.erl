-module(sv).
-export([recibir/0, enviar/3]).

-define(PORT, 5050).
-define(BLOCKSIZE, 4096). % Tamanio del bloque a leer en recibir


recibir() ->
	{ok, Lsock} = gen_tcp:listen(?PORT, [binary, {packet, 0}, {active, false}, {reuseaddr, true}]),
	io:format("Esperando conexion en ~p~n", [?PORT]),
	{ok, Sock} = gen_tcp:accept(Lsock),
	io:format("Conexion aceptada~n"),
	recibir_archivo(Sock),
	gen_tcp:close(Sock),
	gen_tcp:close(Lsock).
% file:write_file("archivo_recibido", Bin),

% Recibe inicialmente el tamanio y luego el archivo propiamente dicho
recibir_archivo(Sock) -> 
	case gen_tcp:recv(Sock,4) of
		{ok, <<Size:32/integer-big>>} ->
			recibir_tam(Sock,Size, <<>>),
			io:format("Archivo recibido.~n");
		_ ->
			io:format("Error al recibir Tamanio~n")
	end.

% Recibe de a BLOCKSIZE los bytes correspondientes al elemento enviado
% Cuando quedan 0 escribe el archivo

recibir_tam(_Sock,0,Acum) ->
	file:write_file("archivo_recibido",Acum),
	io:format("Archivo recibido completo [~p bytes]~n", [byte_size(Acum)]);

recibir_tam(Sock,Restantes,Acum) ->
	ToRead = min(?BLOCKSIZE,Restantes),  
	case gen_tcp:recv(Sock, ToRead) of
		{ok, Datos} ->
			recibir_tam(Sock, Restantes - byte_size(Datos), <<Acum/binary, Datos/binary>>);
		{error, Reason} ->
			io:fwrite("Error al recibir ~p~n", [Reason])
		end.


% Implementacion del cliente
enviar(IP, Puerto, RutaArchivo) ->
	{ok,Bin} = file:read_file(RutaArchivo),
	Size = byte_size(Bin),
	{ok,Sock} = gen_tcp:connect(IP, Puerto, [binary, {packet, 0}, {active, false}]),
	gen_tcp:send(Sock, <<Size:32/integer-big>>),
	io:format("Tamano enviado~n"),
	ok = gen_tcp:send(Sock,Bin),
	io:format("Archivo enviado~n"),
	gen_tcp:close(Sock).