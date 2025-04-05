#!/bin/bash

# inicio del script
clear
echo "-- Iniciando script para auto-configurar dwm y extras --\n"
read -p "Presione ENTER para continuar" a
clear

# descargar my-dots2
git clone https://github.com/TakYzGG/my-dots2

# crear carpetas necesarias
mkdir /home/$user/.config 
mkdir /home/$user/.config/dwmblocks
mkdir /home/$user/.local/bin
mkdir /home/$user/.local/share/fonts
mkdir /home/$user/.suckless

# copiar archivos con los temas
cp -r my-dots2/suckless/temas/* /home/$user/.suckless 

# copiar scripts para dwmblocks
cp my-dots2/scripts/bars/* /home/$user/.config/dwmblocks
chmod +x /home/$user/.config/dwmblocks/*

# copiar scripts de dmenu
cp my-dots2/scripts/dmenu/AppImage /home/$user/.local/bin
cp my-dots2/scripts/dmenu/PowerMenu /home/$user/.local/bin
cp my-dots2/scripts/dmenu/Screenshot /home/$user/.local/bin
cp my-dots2/scripts/dmenu/Suckless-Themes /home/$user/.local/bin
cp my-dots2/scripts/dmenu/Wallpaper /home/$user/.local/bin
chmod +x /home/$user/.local/bin/*

# copiar las fuentes
cp my-dots2/fonts/* /home/$user/.local/share/fonts

# copiar configuracion de bash
cp my-dots2/dots/bashrc /home/$user/.bashrc

# copiar configuracion de picom
cp picom/picom.conf /home/$user/.config

# copiar configuracion de nvim
cp -r /my-dots2/nvim /home/$user/.config 

# final del script
clear
echo "-- Termino la configuracion --"
read -p "Presione ENTER para finalizar" a
