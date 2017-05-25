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
  * [wxamcl.addbtn](#wxamcl.addbtn)
  
**[Create flexible user windows](#create-amc-window)**
  * [wxamcl.createamcwin](#wxamcl.createamcwin)
  * [wxamcl.destroyamcwindow](#wxamcl.destroyamcwindow)
  * [wxamcl.setlefthandler](#wxamcl-setlefthandler)
  * [wxamcl.setrighthandler](#wxamcl-setrighthandler)
  * [wxamcl.setwheelhandler](#wxamcl-setwheelhandler)
  * [wxamcl.setmovehandler](#wxamcl-setmovehandler)
  * [wxamcl.seteventfile](#wxamcl-seteventfile)
  * [wxamcl.mouseevents](#wxamcl-mouseevents)
  * [wxamcl.logwin](#wxamcl-logwin)
  
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
> > The function returns nothing.
> ### wxamcl hidewindow ###
> > Hide a user created window in the client.
> > ### Usage: ###
> > `wxamcl.hidewindow(name)`

```lua
       wxamcl.hidewindow("CaptureWin")
```
> > The funtion returns nothing.
> ### wxamcl destroywindow ###
> > Destroy a user created window in the client.
> > ### Usage: ###
> > `wxamcl.destroywindow(name)`

```lua
       wxamcl.destroywindow("CaptureWin")
```
> > The function returns `nil` if window is not found, otherwise nothing.
> ### wxamcl clearwindow ###
> > Clear the content of a user created window in the client.
> > ### Usage: ###
> > `wxamcl.clearwindow(name)`

```lua
       wxamcl.clearwindow("CaptureWin")
```
> > The function returns nothing.
> ### wxamcl setbackground ###
> > Clear the content of a user created window in the client.
> > ### Usage: ###
> > `wxamcl.setbackground(name, color (optional))`

```lua
            wxamcl.setbackground("CaptureWin") --background will be black
            wxamcl.setbackground("CaptureWin", "red")
            wxamcl.setbackground("CaptureWin", "#00ff00") --green
```
> > The function returns nothing.
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
> > The function returns nothing.
> ### wxamcl destroynb ###
> > Destroy an existing user notebook window for capturing text from the MUD.
> > ### Usage: ###
> > `wxamcl.destroynb(winname))`

```lua
            wxamcl.destroynb("Chatwindow")
```
> > The function returns `nil` if the window does not exist, otherwise nothing.
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
> > `wxamcl.addbtn(toolbarname, text, action, ID)

```lua
         wxamcl.addbtn("Directions", "Up", "up", "1")
		 -- adds a button with label "Up", which will send the command "up" to the MUD, ID needs to be greater than 1 and less than 1000
```
> > The function returns nothing.