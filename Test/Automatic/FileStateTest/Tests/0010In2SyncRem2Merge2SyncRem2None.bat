echo In -- SyncRemove -- MergeSyncRemove -- SyncRemove -- None
setlocal
set TestFile1=%User1TestRoot%\in.txt
set TestFile2=%User2TestRoot%\in.txt
call None2In.bat "%TestFile1%"
call SleepSync.bat "%User2TestRoot%"
removefile "%TestFile1%"
checkin "%TestFile1%"
call SleepUnpack.bat "%User2TestRoot%"
call TestState.bat "%TestFile2%" SyncRemove
checkout "%TestFile2%"
call TestState.bat "%TestFile2%" MergeSyncRemove
uncheckout "%TestFile2%"
call TestState.bat "%TestFile2%" SyncRemove
call Accept.bat "%User2TestRoot%"
call TestState.bat "%TestFile2%" None
endlocal
