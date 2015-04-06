# General Functions #
**[Print, color and output buffer functions](GeneralFuncs#Output_to_screen.md)
  * [wxamcl.echo](GeneralFuncs#wxamcl.echo.md)
  * [wxamcl.echowin](GeneralFuncs#wxamcl.echowin.md)
  * [wxamcl.substitute](GeneralFuncs#wxamcl.substitute.md)
  * [wxamcl.color](GeneralFuncs#wxamcl.color.md)
  * [wxamcl.colorwin](GeneralFuncs#wxamcl.colorwin.md)
  * [wxamcl.colorword](GeneralFuncs#wxamcl.colorword.md)
  * [wxamcl.colorline](GeneralFuncs#wxamcl.colorline.md)
  * [wxamcl.colorall](GeneralFuncs#wxamcl.colorall.md)
  * [wxamcl.getlinenumber](GeneralFuncs#wxamcl.getlinenumber.md)
  * [wxamcl.getline](GeneralFuncs#wxamcl.getline.md)
  * [wxamcl.scroll](GeneralFuncs#wxamcl.scroll.md)
  * [wxamcl.gag](GeneralFuncs#wxamcl.gag.md)** [Send commands](GeneralFuncs#Send_commands_to_the_MUD.md)
  * [wxamcl.send](GeneralFuncs#wxamcl.send.md)
  * [wxamcl.execute](GeneralFuncs#wxamcl.execute.md)

## Output to screen ##
> ### wxamcl.echo ###
> Print text to the main mud window.
> > #### Usage: ####
> > `msg = wxamcl.echo(text, fg-color (optional), bg-color (optional))`

```
		msg = wxamcl.echo("This is a test", "black", "green")
		wxamcl.echo("Text on screen")
		wxamcl.echo("Test me!", "crimson", "deepskyblue")
		wxamcl.echo("Text", "#44cc00", "#000000")
```

> The function returns the text parameter.
> > ### wxamcl.echowin ###

> Print text to a user created window.
> #### Usage: ####
> > `msg = wxamcl.echo(window, text, fg-color (optional), bg-color (optional))`

```
		msg = wxamcl.echo("chat", "This is a test in a window named 'chat'!", "black", "green")
		wxamcl.echo("userwin1", "Text on screen")
		wxamcl.echo("win", "Test me!", "crimson", "deepskyblue")
		wxamcl.echo("window1", "Text", "#44cc00", "#000000")
```

> The function returns the text parameter.
> > ### wxamcl.substitute ###

> Replace text from mud and display the new line instead of the original one. Use this within a trigger (action).
> #### Usage: ####
> > `wxamcl.substitute(oldtext, newtext)`

```
		wxamcl.substitute("Tom", "Jerry")
		wxamcl.substitute("Tom", "^x22J^x123e^x99r^x221r^x167y!")
		
```

> The function returns nothing. You can use all 256 xterm colors via <sup>x0 to </sup>x255 to color parts of the replacement text, this works only with substitute function.
> > ### wxamcl.color ###

> Print colored text to the main mud window without creating a newline to create multicolored text lines.
> > #### Usage: ####
> > `wxamcl.color(text, fg-color (optional), bg-color (optional))`

```
		wxamcl.color("This is a test", "black", "green")
		wxamcl.color("Text on screen")
		wxamcl.color("Test me!", "crimson", "deepskyblue")
		wxamcl.color("Text", "#44cc00", "#000000")
```

> Create a line with multiple colors like this:
```
		wxamcl.echo("")
		wxamcl.color("Text ", "red")
		wxamcl.color("and text in green ", "green")
		wxamcl.color("and text in cyan ", "cyan")
		wxamcl.color("and so on!", "yellow")
```
> The function returns nothing.
> > ### wxamcl.colorwin ###

> Print colored text to a user created window without creating a newline to create multicolored text lines.
> > #### Usage: ####
> > `wxamcl.colorwin(window, text, fg-color (optional), bg-color (optional))`

```
		wxamcl.colorwin("chat", "This is a test", "black", "green")
		wxamcl.colorwin("window", "Text on screen")
		wxamcl.colorwin("win1", "Test me!", "crimson", "deepskyblue")
		wxamcl.colorwin("testwin", "Text", "#44cc00", "#000000")
```

> Create a line with multiple colors like this:
```
		wxamcl.echowin("test", "")
		wxamcl.colorwin("test", "Text ", "red")
		wxamcl.colorwin("test", "and text in green ", "green")
		wxamcl.colorwin("test", "and text in cyan ", "cyan")
		wxamcl.colorwin("test", "and so on!", "yellow")
```
> The function returns nothing.
> > ### wxamcl.colorword ###

> This function colors all occurances of 'word' in the given color combination. Use this within an action.
> > #### Usage: ####
> > `wxamcl.colorword(word, fg-color (optional), bg-color (optional))`

```
		wxamcl.colorword("Tom", "lavender", "maroon")
		wxamcl.colorword("Tom", "#ffffff")
		wxamcl.colorword("Tom", "#44cc00", "#000000")
```

> This will color all occurances of 'Tom' in the given color combination. To find lines with 'Tom' use an action.
> The function returns nothing.
> > ### wxamcl.colorline ###
> > > This function colors a line of text in the output buffer.
> > > #### Usage: ####

> > `wxamcl.colorline(linenumber, fg-color (optional), bg-color (optional))`

```
		wxamcl.colorline(23, "lavender", "maroon")
		wxamcl.colorline(wxamcl.getlinenumber(), "#ffffff")
		wxamcl.colorline(444, "#44cc00", "#000000")
```

> The function returns nothing.
> > ### wxamcl.colorall ###

> This function colors the whole visible output buffer.
> > #### Usage: ####
> > `wxamcl.colorall(fg-color (optional), bg-color (optional))`

```
		wxamcl.colorall("lavender", "maroon")
		wxamcl.colorall("#ffffff")
		wxamcl.colorall("#44cc00", "#000000")
		wxamcl.colorall() -- white and black
```

> The function returns nothing.
> > ### wxamcl.getlinenumber ###

> This function retrieves the number of the last received line.
> > #### Usage: ####
> > `nr = wxamcl.getlinenumber()`

```
		nr = wxamcl.getlinenumber()
```

> The function returns the number of the last received line, ie the number of lines recieved so far.
> > ### wxamcl.getline ###

> This function retrieves the line and all the styles for it as a table.
> > #### Usage: ####
> > `t = wxamcl.getline(linenumber)`

```
		t = wxamcl.getline(33)
		wxamcl.echo("")
		for i,v in ipairs(t) do
		 wxamcl.color(v.text, v.fore, v.back)
		end 
```

> The function returns a table containing the line and its styles. Fields of the table are: text, fore, back, length
> > ### wxamcl.scroll ###

> This function enables or disables scrolling of the main output window.
> > #### Usage: ####
> > `wxamcl.scroll(true|false)`

```
		wxamcl.scroll(true) --normal scrolling
		wxamcl.scroll(false) --do not scroll even if new text arrives from mud
```

> The function returns nothing.
> > ### wxamcl.gag ###

> This function gags the current line from the main output window. Use in an action.
> > #### Usage: ####
> > `wxamcl.gag(line)`

```
		wxamcl.gag(0) --gag current line
```

> The function returns nothing.
## Send commands to the MUD ##
> > ### wxamcl.send ###
> > > Sends text unparsed to the Mud.

> #### Usage: ####
> > `wxamcl.send(command)`

```
		wxamcl.send("say ;)")
		wxamcl.send("quit")
```

> The function returns nothing.
> > ### wxamcl.execute ###
> > > Sends a command to the Mud. The command is parsed as if typed in the command line. You can therefore send aliases, variables and so on.

> #### Usage: ####
> > `wxamcl.execute(command)`

```
		wxamcl.execute("look at "..$target)
		wxamcl.execute("quit")
```

> The function returns nothing.