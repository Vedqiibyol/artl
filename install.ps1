$path = cmd /c "echo %INCLUDE%"
Copy-Item ./artl.h -Destination $path
echo "Installed"