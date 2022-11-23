@echo off
set solution_dir=%~1
set config=%~2
xcopy /e /v /y "%solution_dir%\resources" "%solution_dir%\bin\%config%\resources\"
cd %solution_dir%\
tar --create --file=Game_Build.zip bin