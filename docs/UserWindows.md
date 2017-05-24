# User window Functions #
**[Functions for creating and manipulating user windows](#user-windows)**
  * [wxamcl.createwindow](#wxamcl-createwindow)
  * [wxamcl.showwindow](#wxamcl-showwindow)
  * [wxamcl.hidewindow](#wxamcl-hidewindow)
  * [wxamcl.destroywindow](#wxamcl-destroywindow)
  * [wxamcl.clearwindow](#wxamcl.clearwindow)
  * [wxamcl.setbackground](#wxamcl.setbackground)
  * [wxamcl.createnb](#wxamcl.createnb)
  * [wxamcl.addpage](#wxamcl.addpage)
  * [wxamcl.destroynb](#wxamcl.destroynb)
  * [wxamcl.createtoolbar](#wxamcl.createtoolbar)
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
> > The funtion returns `nil` if window is not found, otherwise nothing.
