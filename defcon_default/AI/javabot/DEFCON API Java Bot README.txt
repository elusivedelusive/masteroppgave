DEFCON API Java Bot
This is the java extension to the DEFCON AI API.

Please see the project homepage for more general information about the api:
http://www.doc.ic.ac.uk/~rb1006/projects:api 
and http://www.introversion.co.uk/defcon/bots/

General Download and Installation Instructions:
If you don't have the bot-enabled Defcon version yet:
    * Windows demo: http://www.introversion.co.uk/defcon/
    * Bot-enabled Defcon executable and framework (see websites above for newest version)

   1. Download and install the Windows demo version of DEFCON.
   2. Unzipped the contents of the Defcon API zip file.
      Copy the contents of the zip file into the directory where you installed 
      Defcon, overwriting the original Defcon.exe (you can make a backup of that).

If you have installed the bot-enabled Defcon version:
    * Unzip the contents of the bot-zip file (which came with this readme) into 
      the AI folder of your Defcon directory, so that the DLL file is in a 
      subfolder of the AI folder. 
      Example:
      C:\DEFCON-Directory\AI\javabot\javabot.dll
      C:\DEFCON-Directory\AI\javabot\source\java\javabot\JBot.java
      C:\DEFCON-Directory\AI\javabot\source\java\javabot\JBot.class
      C:\DEFCON-Directory\Defcon.exe
      ...
    1. Start Defcon.exe
    2. Start a new game or join another game.
    2. Select the bot from the drop-down list when you are in the game lobby.


Included Sourcefiles:

source/bot/*                        C++ part of the Bot, includes the JNI interface to interact with Java.
source/dll/*                        C++ API code, includes connectivity to DEFCON.
source/java/javabot/JBot.java       Java part of the bot.      

The JBot.java contains everything you need to build your java bot. You don't need to touch
the c++ code or recompile the dll if you do not plan to change the behaviour of the Java
Native Interface (JNI), which connects Java with the C++ API of Defcon (If you want
to change the name of the bot, you have to change the path to the java class inside bot.cpp).

The functions available to java are exactly the same as those available to C++. Please note
that the java naming style for methods isn't followed by the API methods (they use an uppercase 
first letter), to be consistent with the function names within the rest of the API.  

By default, a JDK compiler compliance level of java version 1.6 is expected by the API. 
By giving the command line option javaversion="1.4", java 1.4 compliance can be activated.


Feel free to modify and change the code as you see fit.

Changelog:

====================
    javabot v0.9
 23rd February 2009
====================

Initial release.
Please report bugs to me (rb1006@doc.ic.ac.uk).
