-module(intro).
-export([init/0]).
-export([nombre/1]).
-export([apellido/1]).


match_test () ->
	{A,B} = {5,4},
	%{C,C} = {5,4},
	{B,A} = {4,5},
	{D,D} = {5,5}.

string_test () -> [
	helloworld == 'helloworld',
	"helloworld" < 'helloworld',
	helloworld == "helloworld",
	[$h,$e,$l,$l,$o,$w,$o,$r,$l,$d] == "helloworld",
	[104,101,108,108,111,119,111,114,108,100] < {104,101,108,108,111,119,111,114,108,100}, % false
	[] > 1, % true
	[104,101,108,108,111,119,111,114,108,100] == "helloworld"
	].

% Implemente las funciones nombre/1 y apellido/1 para que devuelvan esos campos de las tuplas
% que obtienen como argumento utilizando pattern matching.

nombre (P) ->
	{persona,{nombre,N},_} = P,
	N.

apellido (P) ->
	{persona,_,{apellido, N}} = P,
	N.

tuple_test (P1,P2) ->
	io:fwrite("El nombre de P1 es ~p y el apellido de P2 es ~p~n", [nombre(P1), apellido(P2)]).

%apellido (P) -> ok.
%nombre (P) -> ok.

filtrar_por_apellido([], _) -> [];
filtrar_por_apellido(Personas, Apellido) ->
	[H | T] = Personas,
	case (apellido(H) == Apellido) of
		true -> [nombre(H) | filtrar_por_apellido(T,Apellido)];
		false -> filtrar_por_apellido(T,Apellido)
	end.
%filtrar_por_apellido1 (Personas,A) -> [nombre(P) || P <- Personas, apellido(P) == A].


init() ->
	P1 = {persona, {nombre, "Juan"}, {apellido, "Gomez"}},
	P2 = {persona, {nombre, "Carlos"}, {apellido, "Garcia"}},
	P3 = {persona, {nombre, "Javier"}, {apellido, "Garcia"}},
	P4 = {persona, {nombre, "Rolando"}, {apellido, "Garcia"}},
	match_test(),
	tuple_test(P1,P2),
	string_test (),
	Garcias = filtrar_por_apellido([P4,P3,P2,P1], "Garcia"),
	Garcias.