#!/bin/bash
#UNIX Operator development version, simple menu-based interface for UNIX systems.
#Copyright (C) 2014  Alex Martin

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.

SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Tests if an existing installation of UNIX Operator exists for this user.
# bool testForExistingInstall
testForExistingInstall=""
function testForExistingInstall()
{
  if test -d ~/.uop
  then
    testForExistingInstall="true"
  else
    testForExistingInstall="false"
  fi
}

# Updates UNIX Operator to the version the installer is packaged with.
# void doUpdate
function doUpdate()
{
  cd "$SCRIPTDIR"
  echo "Creating directory structure in update directory..."
  mkdir -v ~/.uop/update/apis ~/.uop/update/programs
  sleep 2
  echo "Copying files..."
  cp -v ./gpl-3.0.txt ./uop ./version ./installer.sh ~/.uop/update
  cp -v ./apis/* ~/.uop/update/apis
  cp -v ./programs/* ~/.uop/update/programs
  sleep 2
  echo "Launching UNIX Operator to finish update(Please quit UNIX Operator after menu opens)..."
  sleep 2
  uop
}

# Performs the installation
# void doInstall
function doInstall()
{
  cd "$SCRIPTDIR"
  echo "Performing installation..."
  sleep 2
  echo "Creating directory structure..."
  mkdir -v ~/.uop ~/.uop/apis ~/.uop/install ~/.uop/update ~/.uop/programs
  sleep 2
  echo "Copying files..."
  cp -v ./gpl-3.0.txt ./credits.txt ./uop ./version ./installer.sh ~/.uop
  cp -v ./apis/* ~/.uop/apis
  cp -v ./programs/* ~/.uop/programs
  sleep 2
  echo "Backing up config files..."
  cp ~/.bashrc ~/.bashrc.old
  cp ~/.bash_profile ~/.bash_profile.old
  echo "Configuring .bash_profile to source .bashrc(don't worry if you don't know what this means)..."
  echo "source ~/.bashrc" >> ~/.bash_profile
  echo "Configuring .bashrc to add ~/.uop to the path..."
  echo "PATH=\"\$PATH:\$HOME/.uop\"" >> ~/.bashrc
  sleep 2
  echo "Checking if successful..."
  if test -d ~/.uop -a -f ~/.uop/uop -a -f ~/.uop/apis/ErrorHandling -a -f ~/.uop/programs/TextEditor
  then
    echo "Installation complete!"
    sleep 2
  else
    echo "installer.sh: Installation failed! Maybe mkdir or cp doesen't support multiple operands?" >&2
    sleep 2
  fi
}

# Start installing UNIX Operator
# void startInstall
function startInstall()
{
  clear
  testForExistingInstall
  if test $testForExistingInstall = "true"
  then
    source ~/.uop/version
    echo "An installation of UNIX Operator version $uopVersion-$uopVersionPostfix has been detected."
    echo "What would you like to do?"
    local selection=""
    PS3="Make your selection[1,2]: "
    local options=("Update the existing installation" "Remove the existing installation and reinstall" "Cancel")
    select selection in "${options[@]}"
    do
      case $selection in
        "Update the existing installation")
          doUpdate
          break
        ;;
        "Remove the existing installation and reinstall")
          startUninstall --force
          doInstall
          break
        ;;
        "Cancel")
          clear
          break
        ;;
      esac
    done
  else
    doInstall
  fi
}

# Performs the uninstallation
# void doUninstall
function doUninstall()
{
  echo "Performing uninstall..."
  echo "Removing ~/.uop..."
  rm -rv ~/.uop
  sleep 2
  echo "Restoring config files..."
  rm -v ~/.bashrc
  mv -v ~/.bashrc.old ~/.bashrc
  rm -v ~/.bash_profile
  mv -v ~/.bash_profile.old ~/.bash_profile
  sleep 2
}

# Start uninstalling UNIX Operator
# void startUninstall [--force]
function startUninstall()
{
  local confirm1="n"
  local confirm2="n"
  testForExistingInstall
  if test $testForExistingInstall = "true"
  then
    echo -n "Confirm uninstall of UNIX Operator version $uopVersion-$uopVersionPostfix (this will remove ~/.uop and all it's contents, including programs, as well as restoring .bashrc.old and .bash_profile.old. Please make sure these files are correct.)[y,N]? "
    read confirm1
    if test $confirm1 = "y"
    then
      echo -n "Are you sure[y,N]? "
      read confirm2
      if test $confirm2 = "y"
      then
        doUninstall
      fi
    fi
  else
    echo "installer.sh: No existing install to remove!" >&2
  fi
}

# Closes the installer
# void close
function close()
{
  PS3=""
  clear
  exit
}

# Displays the main menu for the UNIX Operator installer
# void installerMenu
function installerMenu()
{
  clear
  echo "Installer menu"
  local selection=""
  PS3="Make your selection[1,2,3]: "
  local options=("Install or update UNIX Operator" "Remove an existing installation of UNIX Operator" "Quit")
  select selection in "${options[@]}"
  do
    case $selection in
      "Install or update UNIX Operator")
        startInstall
        break
      ;;
      "Remove an existing installation of UNIX Operator")
        startUninstall
        break
      ;;
      "Quit")
        close
        break
      ;;
    esac
  done
}

#void main
function main()
{
  cd $SCRIPTDIR
  echo "Welcome to the UNIX Operator installer."
  echo "This program will install or remove UNIX Operator for the current user."
  while true
  do
  installerMenu
  done
}

main
