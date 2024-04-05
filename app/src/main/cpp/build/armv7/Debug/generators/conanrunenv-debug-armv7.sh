script_folder="C:\Users\tts\Desktop\VTMaps\app\src\main\cpp\build\armv7\Debug\generators"
echo "echo Restoring environment" > "$script_folder\deactivate_conanrunenv-debug-armv7.sh"
for v in 
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder\deactivate_conanrunenv-debug-armv7.sh"
    else
        echo unset $v >> "$script_folder\deactivate_conanrunenv-debug-armv7.sh"
    fi
done

