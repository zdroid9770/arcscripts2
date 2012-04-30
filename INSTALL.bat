@ECHO OFF
TITLE arcscripts2 patch installation tool

:TOP
CLS
ECHO.
echo that this tool will can to work, you need to be installed git in windows prompt
echo applying patch
@cd ..\..\
git am src\arcscripts2\patches\arcscripts2_patch.patch
echo
echo done!
echo thanks for using ArcScripts2
pause