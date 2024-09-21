@echo off
setlocal enabledelayedexpansion enableextensions

set relink_needed=0
set cc=clang
set numjobs=1

if not exist bin mkdir bin


for /r src %%f in (*.c) do (
    set obj=bin\%%~nf.obj
    set src=%%f
    if not exist !obj! (
        echo "!cc! -c !src! -o !obj! -Isrc -Isrc/lua"
        clang -Isrc -Isrc/lua -c !src! -o !obj!
        set relink_needed=1
    )
)