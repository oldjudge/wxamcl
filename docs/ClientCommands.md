# Client Commands #
> Default commands sign is #. Change it under Menu Extras->Preferences->Tab: General.
> Type #help to get a list of all available commands.

  * [Commands](ClientCommands#Commands.md)
    * [#capend](ClientCommands#capend.md)
    * [#capstart](ClientCommands#capstart.md)
    * [#capturenb](ClientCommands#capturenb.md)
    * [#capturewin](ClientCommands#capturewin.md)
    * [#clearwin](ClientCommands#clearwin.md)
    * [#connect](ClientCommands#connect.md)
    * [#connect6](ClientCommands#connect6.md)
    * [#debugGMCP](ClientCommands#debugGMCP.md)
    * [#func](ClientCommands#func.md)
    * [#gag](ClientCommands#gag.md)
    * [#gagwin](ClientCommands#gagwin.md)
    * [#help](ClientCommands#help.md)
    * [#htmllog](ClientCommands#htmllog.md)
    * [#info](ClientCommands#info.md)
    * [#loadprofile](ClientCommands#loadprofile.md)
    * [#log](ClientCommands#log.md)
    * [#media](ClientCommands#media.md)
    * [#mxp](ClientCommands#mxp.md)
    * [#pwd](ClientCommands#pwd.md)
    * [#raw](ClientCommands#raw.md)
    * [#refreshwin](ClientCommands#refreshwin.md)
    * [#resume](ClientCommands#resume.md)
    * [#script](ClientCommands#script.md)
    * [#setvar](ClientCommands#setvar.md)
    * [#test](ClientCommands#test.md)
    * [#tscript](ClientCommands#tscript.md)

## Commands ##
> ## capend ##
> > End capturing of text to an extra window. See #capstart.

> ## capstart ##
> > Start capturing text to an extra window, use in an action.
> > Usage:
```
   #capstart(windowname, true|false)
```
> > > Starts capturing text to the window called 'windowname', will create the window if not already there.
> > > If second parameter is 'true' the triggered line will be gagged from output of new window.

> ## capturenb ##
> > Capture a line of text to a page of a notebook user window.
> > Usage:
```
   #capturenb(windowname, pagename, number_of_lines, true|false)
   #capturenb("Test", "test1", "1", "true")
```
> > > Capture text to 'windowname'-window, show in page 'pagename'.
> > > Param 3 tells how many lines to capture. param 4 true gags the line/the lines from output.
> > > Windows are created as needed.

> ## capturewin ##
> > Capture a line of text to user window.
> > Usage:
```
   #capturewin(windowname, number_of_lines, true|false)
   #capturewin("test", "1", "false")
```
> > > Capture text to 'windowname'-window.
> > > Param 2 tells how many lines to capture. param 3 'true' gags the line/the lines from output.
> > > Windows are created as needed.

> ## clearwin ##
> > Clear the content of a user window.
> > Usage:
```
   #clearwin(windowname)
```
> > Example usage in a trigger:
```
   #clearwin("Help")
   #capstart("Help", "true")
   #gagwin("Help", "0")
```

> ## connect ##
> > Connect the client to a mud.
> > Usage:
```
  #connect(mudname, port)
  #connect("aardmud.org", "4000")
```

> ## connect6 ##
> Connect the client to a mud via IPv6 protocol.
> Usage:
```
 #connect6(mudname, port)
 #connect6("aardmud.org", "4000")
```
> ## debugGMCP ##
> > Write gmcp messages to a file named "debuggmcp.txt". The file will be saved in the working directory.
> > Usage:
```
  #debugGMCP(on|off)
```

> ## func ##
> > Call a function in a lua script file (located in the lua subdirectory) directly.
> > Usage:
```
   #func(filename, function)
   #func("functest.lua", "Test('green', 'red')")
```
> > Calls the Test function in the scriptfile functest.lua.

> ## gag ##
> > Gag current line in the main output window. Use in a trigger.
> > Usage:
```
   #gag(linenumber)
   #gag("0")
```
> > Parameter has currently no function. Gags always the current line, that is the line, which triggered the action.

> ## gagwin ##
> > Gag current line in a user window.
> > Usage:
```
   #gagwin(windowname, linenumber)
   #gagwin("test", "0")
```
> > Second parameter has currently no function. Gags always the current line, that is the line, which triggered the action.

> ## help ##
> > List all client commands.
> > Usage:
```
   #help
```

> ## htmllog ##
> > Start logging mud text in html-format.
> > Usage:
```
   #htmllog(logfile, true|false)
```
> > Second parameter starts or stops logging. File will be located in the log subdirectory.

> ## info ##
> > Show some infos about used libraries, gmcp elements, mxp elements, mccp compression.
> > Usage:
```
   #info
```

> ## loadprofile ##
> > Load a client profile file manually.
> > Usage:
```
   #loadprofile(profilename)
   #loadprofile("aard.lua")
```
> > Profiles are simple lua files and must be located in the profile subdirectory. They save all actions, aliases etc. and all per char settings.

> ## log ##
> > Start logging mud text as plain text.
> > Usage:
```
   #log(logfile, ansicodes{true|false}, timestamps{true|false})
```
> > Second parameter determines if ansicodes will be logged or not. Third parameter determines if timestamps are logged or not. File will be located in the log subdirectory.

> ## media ##
> > Play any wxWidgets supported media file.
> > Usage:
```
   #media(filename)
   #media("song.mp3")
   #media("movie.wmv")
   #media("sound.wav")
```

> ## mxp ##
> > Turn mxp parsing in the client manually on or off.
> > Usage:
```
   #mxp(on|off)
   #mxp("on")
```

> ## pwd ##
> > Send the password from the currently loaded profile (if any) to the mud.
> > Usage:
```
   #pwd
```

> ## raw ##
> > Save the raw incoming mud packets to a file called raw.dat (in the log subdirectory).
> > Usage:
```
   #raw
```

> ## refreshwin ##
> > Refresh (redraw) the contents of a user window.
> > Usage:
```
   #refreshwin(windowname)
   #refreshwin("Testwin")
```

> ## resume ##
> > Do not use, only used internally with the waitfor and wait script commands.

> ## script ##
> > Load a script (located in the scripts subdirectory) and execute it.
> > Usage:
```
   #script(scriptfile)
   #script("test.lua")
```
> > Loads the script and executes it. This will block the client, see also tscript command.

> ## setvar ##
> > Set the value of a client variable. The variable must already exist (ie be defined).
> > Usage:
```
   #setvar(variable, content)
   #setvar("health", "4000")
```

> ## test ##
> > Simulate incoming mud text, use this to test your triggers.
> > Usage:
```
   #test(walloftext)
   #test("I am incoming mudtext!")
```

> ## tscript ##
> > Load a script (located in the scripts subdirectory) and execute it.
> > Usage:
```
   #tscript(scriptfile)
   #tscript("test.lua")
```
> > Loads the script and executes it. This will NOT block the client, see also script command. You need this command if you use wait or waitfor in your script!