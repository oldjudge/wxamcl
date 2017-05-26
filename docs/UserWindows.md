# User window Functions #
**[Functions for creating and manipulating user windows](#user-windows)**
  * [wxamcl.createwindow](#wxamcl-createwindow)
  * [wxamcl.showwindow](#wxamcl-showwindow)
  * [wxamcl.hidewindow](#wxamcl-hidewindow)
  * [wxamcl.destroywindow](#wxamcl-destroywindow)
  * [wxamcl.clearwindow](#wxamcl-clearwindow)
  * [wxamcl.setbackground](#wxamcl-setbackground)
  * [wxamcl.createnb](#wxamcl-createnb)
  * [wxamcl.addpage](#wxamcl-addpage)
  * [wxamcl.destroynb](#wxamcl-destroynb)
  * [wxamcl.createtoolbar](#wxamcl-createtoolbar)
  * [wxamcl.addbtn](#wxamcl-addbtn)
  * [wxamcl.logwin](#wxamcl-logwin)
  
**[Create windows for user defined gauges](#create-gauge-window-and-gauges)**
   * [wxamcl.gauge.createwindow](#wxamcl-gauge-createwindow)
   * [wxamcl.gauge.update](#wxamcl-gauge-update)
   * [wxamcl.gauge.new](#wxamcl-gauge-new)
   * [wxamcl.gauge.setsize](#wxamcl-gauge-setsize)
   * [wxamcl.gauge.setcolor](#wxamcl-gauge-setcolor)
   * [wxamcl.gauge.setlabel](#wxamcl-gauge-setlabel)
   * [wxamcl.gauge.delete](#wxamcl-gauge-delete)
  
**[Create flexible user windows](#create-flexible-user-window)**
  * [wxamcl.createamcwin](#wxamcl-createamcwin)
  * [wxamcl.destroyamcwindow](#wxamcl.destroyamcwindow)
  * [wxamcl.setlefthandler](#wxamcl-setlefthandler)
  * [wxamcl.setrighthandler](#wxamcl-setrighthandler)
  * [wxamcl.setwheelhandler](#wxamcl-setwheelhandler)
  * [wxamcl.setmovehandler](#wxamcl-setmovehandler)
  * [wxamcl.seteventfile](#wxamcl-seteventfile)
  * [wxamcl.mouseevents](#wxamcl-mouseevents)
  
  
## User Windows ##
> ### wxamcl createwindow ###
> > Create a user window for capturing mud output
> > ### Usage: ###
> > `wxamcl.createwin(name, backgroundcolor (optional))`

```lua
        wxamcl.createwin("CaptureWin") -- window background will be black
        wxamcl.createwin("CaptureWin", "red") -- window background will be red
        wxamcl.createwin("CaptureWin", "#ff00ff")
```
> > The function returns nothing. See also the [#capturewin client command.](ClientCommands.md)
> ### wxamcl showwindow ###
> > Show a user created window in the client.
> > ### Usage: ###
> > `wxamcl.showwindow(name)`

```lua
       wxamcl.showwindow("CaptureWin")
```
> > The function returns `nil` if window is not found, otherwise `true`.
> ### wxamcl hidewindow ###
> > Hide a user created window in the client.
> > ### Usage: ###
> > `wxamcl.hidewindow(name)`

```lua
       wxamcl.hidewindow("CaptureWin")
```
> > The funtion returns `nil` if name wasn't valid, otherwise `true`.
> ### wxamcl destroywindow ###
> > Destroy a user created window in the client.
> > ### Usage: ###
> > `wxamcl.destroywindow(name)`

```lua
       wxamcl.destroywindow("CaptureWin")
```
> > The function returns `nil` if window is not found, otherwise `true`.
> ### wxamcl clearwindow ###
> > Clear the content of a user created window in the client.
> > ### Usage: ###
> > `wxamcl.clearwindow(name)`

```lua
       wxamcl.clearwindow("CaptureWin")
```
> > The function returns `nil` if window is not found, otherwise `true`.
> ### wxamcl setbackground ###
> > Clear the content of a user created window in the client.
> > ### Usage: ###
> > `wxamcl.setbackground(name, color (optional))`

```lua
            wxamcl.setbackground("CaptureWin") --background will be black
            wxamcl.setbackground("CaptureWin", "red")
            wxamcl.setbackground("CaptureWin", "#00ff00") --green
```
> > The function returns `nil` if window is not found, otherwise `true`.
> ### wxamcl createnb ###
> > Create a user notebook window for capturing text from the MUD, also creates the (first) tabbed page of the notebook. See also
> > [#capturenb client command](ClientCommands.md)
> > ### Usage: ###
> > `wxamcl.createnb(winname, pagename))`

```lua
            x=wxamcl.createnb("Chatwindow", "Gossip")
```
> > The function returns a light userdata, ie the address of the newly created window.
> ### wxamcl addpage ###
> > Create a page for an existing user notebook window for capturing text from the MUD.
> > ### Usage: ###
> > `wxamcl.addpage(winname, pagename))`

```lua
            wxamcl.addpage("Chatwindow", "Questions")
```
> > The function returns `nil`if winname was not valid, otherwise `true`.
> ### wxamcl destroynb ###
> > Destroy an existing user notebook window for capturing text from the MUD.
> > ### Usage: ###
> > `wxamcl.destroynb(winname))`

```lua
            wxamcl.destroynb("Chatwindow")
```
> > The function returns `nil` if the window does not exist, otherwise `true`.
> ### wxamcl createtoolbar ###
> > Create a user defined toolbar.
> > ### Usage: ###
> > `wxamcl.createtoolbar(toolbarname)`

```lua
           wxamcl.createtoolbar("Directions")
```
> > The function returns nothing.
> ### wxamcl addbtn ###
> > Add a button to an existing user created toolbar.
> > ### Usage: ###
> > `wxamcl.addbtn(toolbarname, text, action, ID)`

```lua
         wxamcl.addbtn("Directions", "Up", "up", "1")
		 -- adds a button with label "Up", which will send the command "up" to the MUD, ID needs to be greater than 1 and less than 1000
```
> > The function returns nothing.
> ### wxamcl logwin ###
> > Log the content of an user window (not amc-user-window). Name of the logfile will be 'windowname.log', will be in the logs subdirectory.
> > Next logging overwrites the old logfile!
> > ### Usage: ###
> > `wxamcl.logwin(windowname, on_off)`

```lua
         wxamcl.loginw("Gossip", "true") --start logging the window
		 wxamcl.logwin("Gossip", "false") --stop logging
```
> > The function returns `nil`if windowname was not valid, `false`if logfile couldn't be created, `true` otherwise.

## Create gauge window and gauges ##
> ### wxamcl gauge createwindow ###
> > Create an user window, specifically meant for displaying gauges (Hitpoints, Mana, Moves, Experience etc.).
> > ### Usage: ###
> > `wxamcl.gauge.createwindow(windowname)`

```lua
         wxamcl.gauge.createwindow("Stats")
```
> > The function returns nothing.
> ### wxamcl gauge new ###
> > Add a new gauge to an existing gauge window.
> > ### Usage: ###
> > `wxamcl.gauge.new(windowname, gaugename, variable1, variable2, color foreground(optional), color background(optional), vertical(optional))`

```lua
         wxamcl.gauge.new("Stats", "Hps", "hpcur", "hpmax")
		 wxamcl.gauge.new("Stats", "Mana", "mana", "manamax", "yellow", "blue", "true") -- will display a vertical gauge
```
> > The function returns `true`, `nil`if windowname wasn't valid. The variables need to hold the values to display, variable1 needs to have current value, variable2 needs to have maximal value.
> > Those variables need to be defined before calling this function.
> ### wxamcl gauge update ###
> > Update the gauge with current values.
> > ### Usage: ###
> > `wxamcl.gauge.update(windowname, gaugename)

```lua
         x=wxamcl.gauge.update("Stats", "Hps")
		 -- in reality will look like this, if we get the values eg through GMCP protocol, code will be in eventhandler for GMCP data received
		 -- standard will be OnGMCPData(data) in event handler file 'events.lua'
		 if (data == "charvitals") then
		 wxamcl.var.set("hpscur", wxamcl.GMCP.charvitals.hp) --aardwolf
		 wxamcl.var.set("manacur", wxamcl.GMCP.charvitals.mana)
		 end
		 if (data=="charmaxstats") then
		 wxamcl.var.set("hps", wxamcl.GMCP.charmaxstats.maxhp) --aardwolf
         wxamcl.var.set("mana", wxamcl.GMCP.charmaxstats.maxmana)
		 end
		 wxamcl.gauge.update("Stats", "Hps")
		 wxamcl.gauge.update("Stats", "Mana")
		 -- to create this gauge do
		 wxamcl.gauge.creatwindow("Stats")
		 wxamcl.gauge.new("Stats", "Hps", "hpscur", "hps", "green", "#999999")
		 wxamcl.gauge.setsize("Stats", "Hps", "10", "10", "200", "40")
```
> > The function returns `true` or `nil`if windowname or gaugename wasn't valid.
> ### wxamcl gauge setsize ###
> > Set the size and position of the gauge in the user window, means where it is drawn and how large it is.
> > ### Usage: ###
> > `wxamcl.gauge.setsize(windowname, gaugename, x, y, cx, cy)`

```lua
         x=wxamcl.gauge.setsize("Stats", "Hps", "10", "10", "40", "200") --vertical layout
         value=wxamcl.gauge.setsize("Stats", "Hps", "10", "10", "200", "40") --horizontal layout
```
> > The function returns `nil` if windowname or gaugename wasn't valid, otherwise returns `true`.
> ### wxamcl gauge setcolor ###
> > Set the colors of the gauge in the user window.
> > ### Usage: ###
> > `wxamcl.gauge.setcolor(windowname, gaugename, color foreground (optional), color background (optional), alarm color (optional))`

```lua
         x=wxamcl.gauge.setcolor("Stats", "Hps") -- colors white, black, red
         value=wxamcl.gauge.setcolor("Stats", "Hps", green, "grey", "purple")
```
> > The function returns `nil` if windowname or gaugename wasn't valid, otherwise returns `true`. Alarm color is a color which will be displayed if current value is below 30% of max value.
> ### wxamcl gauge setlabel ###
> > Set label of a gauge.
> > ### Usage: ###
> > `wxamcl.gauge.setlabel(windownamen, gaugename, label)`

```lua
         x=wxamcl.gauge.setlabel("Stats", "Hps", "Life")
```
> >  The function returns `nil` if windowname or gaugename wasn't valid, otherwise returns `true`.
> ### wxamcl gauge delete ###
> > Delete a gauge.
> > ### Usage: ###
> > `wxamcl.gauge.delete(windownamen, gaugename)`

```lua
         x=wxamcl.gauge.delete("Stats", "Hps")
```
> >  The function returns `nil` if windowname or gaugename wasn't valid, otherwise returns `true`.
## Create flexible user window ##
> These windows are very controllable by the user via lua-scripting. A common use would be implementation of a mapper for a MUD.
> > ### wxamcl createamcwin ###
> > Create a flexible user window, eg. for drawing on it.
> > ### Usage: ###
> > `wxamcl.createamcwin(windowname, backgroundcolor (optional=black))`

```lua
         wxamcl.createamcwin("Mapper")
		 wxamcl.createamcwin("Mapper", "grey")
```
> > The function returns nothing.
> > ### wxamcl destroyamcwindow ###
> > Destroy a with wxamcl.createamcwin created user window.
> > ### Usage: ###
> > `wxamcl.destroyamcwindow(windowname)`

```lua
         wxamcl.destroyamcwindow("Mapper")
```
> > Returns `nil` if windowname wasn't found, otherwise true.
> > ### wxamcl setlefthandler ###
> > Set the function for handling left button mouse events in the amc-user-window. Standard: OnMouseLeft(x,y)
> > ### Usage: ###
> > `wxamcl.setlefthandler(winname, functionname)`

```lua
         wxamcl.setlefthandler("Mapper", "OnMouseLeft")
```
> > The function returns nothing.
> > ### wxamcl setrighthandler ###
> > Set the function for handling right button mouse events in the amc-user-window. Standard: OnMouseRight(x,y)
> > ### Usage: ###
> > `wxamcl.setrighthandler(winname, functionname)`

```lua
         wxamcl.setrighthandler("Mapper", "OnMouseRight")
```
> > The function returns nothing.
> > ### wxamcl setwheelhandler ###
> > Set the function for handling mouse wheel events in the amc-user-window. Standard: OnMouseWheel(rotation)
> > ### Usage: ###
> > `wxamcl.setwheelhandler(winname, functionname)`

```lua
         wxamcl.setwheelhandler("Mapper", "OnMouseWheel")
```
> > The function returns nothing.
> > ### wxamcl setmovehandler ###
> > Set the function for handling move mouse events in the amc-user-window. Standard: OnMouseMove(x,y)
> > ### Usage: ###
> > `wxamcl.setmovehandler(winname, functionname)`

```lua
         wxamcl.setmovehandler("Mapper", "OnMouseMove")
```
> > The function returns nothing.
> > ### wxamcl seteventfile ###
> > Set the file where all the handlers for the window should be defined. Standard: events.lua
> > ### Usage: ###
> > `wxamcl.seteventfile(winname, filename)`

```lua
         wxamcl.seteventfile("Mapper", "mapper_events.lua")
```
> > The function returns nothing.
> > ### wxamcl mouseevents ###
> > Enable or disable mouseevent handling for the amc-user-window. Standard: disabled
> > ### Usage: ###
> > `wxamcl.mouseevents(winname, true_false)`

```lua
         wxamcl.mouseevents("Mapper", "true")
		 wxamcl.mouseevents("Mapper", "false")
```
> > The function returns nothing.