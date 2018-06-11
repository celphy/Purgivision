# Purgivision
A tool that automatically purges Activisions games from the Battle.net launcher (for now). As the author I take no responsibility for any
issues that might arise such as your hardware/files/pet/... being damaged or even your Battle.net account being banned.

Usage
=====

The first release is extremely untested (my own 2 devices) and might not work for you at all.

Place the correct version of Purgivision in next to your Battle.net.exe in the installation folder. Exit the launcher and execute Purgivision. After the text output has disappeared you can start the launcher again and the Activison games should no longer be visible.

Compiling it yourself
---------------------

As this program heavily relies on the https://github.com/ladislav-zezula/StormLib you will need to provide the source code in a folder called Stormlib next to the main.cpp. In addition to that the compiled binary .lib needs to be located as follows ./libs/XY.lib or for x86 in ./libs/x86/XY.lib.

What to expect
--------------

This is very much work in progress but I want to provide an automatic patcher that removes the Activision games and possibly some adverts from the bloated Battle.net Launcher.
