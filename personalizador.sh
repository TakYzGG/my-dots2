#!/bin/sh

# inicio del script
clear
echo "-- Iniciando script de personalizacion --\n"
read -p "Presione ENTER para continuar" a
clear

# opciones usuario
read -p "Nombre de usuario: " user
clear

echo "-- personalizar --"
echo "[1] Windows managar (wm)"
echo "[2] Desktop environment (de)"
echo "[3] Extras"
read -p "Opcion: " personalizar
clear

case $personalizar in
	1) echo "-- Windows manager --"
	   echo "[1] Bspwm"
	   echo "[2] Dwm"
	   echo "[3] Fluxbox"
	   echo "[4] I3 wm"
	   echo "[5] Openbox"
	   read -p "Opcion: " wm
	   clear
	   ;;
	2) echo "-- Desktop environment --"
	   echo "[1] Kde"
	   echo "[2] Lxde"
	   echo "[3] Mate"
	   echo "[4] Xfce"
	   read -p "Opcion: " de
	   clear
	   ;;
	3) echo "-- Extras --"
	   echo "[1] Bash"
	   echo "[2] Dmenu / Simple terminal (st)"
	   echo "[3] Neo vim"
	   echo "[4] Vim"
	   echo "[5] Zsh"
	   read -p "Opcion: " extras
	   clear
	   ;;
	*) echo "Respuesta no valida" ;;
esac

# descargar my-dots2
git clone https://github.com/TakYzGG/my-dots2

# archivos generales
if [ "$personalizar" -eq 1 ]; then
	mkdir /home/$user/.local/bin
	cp my-dots2/scripts/dmenu/AppImage /home/$user/.local/bin
	cp my-dots2/scripts/dmenu/PowerMenu /home/$user/.local/bin
	cp my-dots2/scripts/dmenu/Screenshot /home/$user/.local/bin
	cp my-dots2/scripts/dmenu/Wallpaper /home/$user/.local/bin
	chmod +x /home/$user/.local/bin*
	cp picom/picom.conf /home/$user/.config

fi

case $wm in
	# bspwm
	1) xbps-install -y bspwm sxhkd lxterminal polybar 
	   ;;

	# dwm
	2) mkdir /home/$user/.config mkdir /home/$user/.config/dwmblocks && mkdir /home/$user/.suckless
	   cp -r my-dots2/suckless/temas/* /home/$user/.suckless 
	   cp my-dots2/scripts/bars/* /home/$user/.config/dwmblocks
	   chmod +x /home/$user/.config/dwmblocks/*
	   cp my-dots2/scripts/dmenu/Suckles-Themes /home/$user/.local/bin
	   ;;

	# fluxbox
	3) xbps-install -y fluxbox lxterminal
	   ;;

	# i3 wm
	4) xbps-install -y i3 i3-gaps i3blocks lxterminal 
	   ;;

	# openbox
	5) xbps-install -y openbox obconf tint2 lxterminal
	   ;;

	*) echo "Respuesta no valida" ;;
esac

case $de in
	# kde
	1) xbps-install -y kde5-baseapps 
	   ;;

	# lxde
	2) xbps-install -y lxde
	   ;;

	# mate
	3) xbps-install -y mate
	   ;;

	# xfce
	4) xbps-install -y xfce4
	   ;;

	*) echo "Respuesta no valida" ;;
esac

case $extras in
	# bashrc
	1) cp /home/$user/my-dots2/dots/bashrc /home/$user/.bashrc
	   ;;

	# dmenu / simple terminal 
	2) mkdir /home/$user/.suckless
	   cp -r my-dots2/suckless/temas/* /home/$user/.suckless 
	   ;;

	# neo vim
	3) cp -r /home/$user/my-dots2/nvim /home/$user/.config 
	   ;;

	# vim
	4) cp -r /home/$user/my-dots2/vim/* /home/$user
	   ;;
	   
	# zshrc
	5) cp /home/$user/my-dots2/dots/zshrc /home/$user/.zshrc
	   ;;

	*) echo "Respuesta no valida" ;;
esac
