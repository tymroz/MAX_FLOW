@echo off
rem Uruchamianie programu dla k=3,...,10 oraz i=1,...,k

rem Ścieżka do Twojego programu (zmień na odpowiednią lokalizację)
set PROGRAM=a.exe

rem Pętla po wartościach k (od 3 do 10)
for /L %%k in (3, 1, 10) do (
    rem Pętla po wartościach i (od 1 do k)
    for /L %%i in (1, 1, %%k) do (
        rem Uruchomienie programu z odpowiednimi argumentami
        echo Uruchamianie programu z k=%%k i=%%i
        %PROGRAM% --size %%k --degree %%i
    )
)

echo Zakończono uruchamianie programu.
pause
