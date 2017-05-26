# Action functions #
**[Functions for creating and manipulating actions (aka triggers) via lua scripting.](#actions)**
 * [wxamcl.action.new](#wxamcl-action-new)
 * [wxamcl.action.get](#wxamcl-action-get)
 * [wxamcl.action.getuserdata](#wxamcl-action-getuserdata)
 * [wxamcl.action.delete](#wxamcl-action-delete)
 * [wxamcl.action.enable](#wxamcl-action-enable)
 * [wxamcl.action.getpattern]
 * [wxamcl.action.setpattern]
 * [wxamcl.action.getac]
 * [wxamcl.action.setac]
 * [wxamcl.action.getpriority]
 * [wxamcl.action.setpriority]
 * [wxamcl.action.getcolmatch]
 * [wxamcl.action.setcolmatch]
 * [wxamcl.action.enableall]
 * [wxamcl.action.disableall]
 * [wxamcl.action.getall]
 * [wxamcl.action.getgroup]
 * [wxamcl.action.enablegroup]
 * [wxamcl.action.delgroup]
 * [wxamcl.action.execute]
 
 
 **Using `wxamcl.Action`**
 > The client will provide all actions via an internal table, which is accessible under `wxamcl.Action`.
 > If you have created an action with the label `Gossip' you can simply access all of its properties like this:
 ```lua
         wxamcl.echo(wxamcl.Action.Gossip.pattern)
```
> Fields of this table are: pattern, action, group, on, priority, colmatch, lines, matchcount, script
> *You cannot use this to change values, you have to use the methods like wxamcl.action.setpattern etc. for this purpose.*
> **You can create a new action like this: `wxamcl.Action.Newbie = {pattern="newbie", action='#capturewin("Newbie", "1", "true")', group="chat", on=true}`**
> An action with the label "Newbie" must not exist in this case. lua will call the __newindex metamethod to create a new action then.
> You can access an action also like this: `t=wxamcl.Action.gossip`. "gossip" must exist. `t` will be a table with the fields: label, pattern, action, group, on, priority, colmatch, lines, matchcount, script.

## Actions ##
> ### wxamcl action new ###
> Create a new action (trigger).
> > ### Usage: ###
> > `wxamcl.action.new(name, table{pattern, action, group, on, priority, colmatch}(optional))`

```lua
         ud = wxamcl.action.new("gossip", {pattern=".*(gossips) '.", action='#capturewin("Gossip", "1", "true")', group="chat", on=true, priority=100,colmatch=-1})
         ud = wxamcl.action.new("newbie") -- will fill out all other fields with default values
```
> The function returns a userdatum, which can be used in other script function calls with wxamcl.action.
> ### wxamcl action get ###
> > Get the properties of an action (trigger) as a lua table.
> > ### Usage: ###
> > `wxamcl.action.get(actionname|userdatum)`

```lua
         t=wxamcl.action.get("Gossip")
		 t=wxamcl.action.get(ud)
```
> > The function returns `nil`if action is not found, otherwise a table representing the action. Fields of the table are: pattern, action, group, on, priority, colmatch, lines, script, matchcount.
> ### wxamcl action getuserdata ###
> > Get the userdatum of an action.
> > ### Usage: ###
> > `wxamcl.action.getuserdata(actionname)`

```lua
         ud = wxamcl.action.getuserdata("gossip")
```
> > The function returns `nil`if action not found, otherwise a userdatum representing the action.
> ### wxamcl action delete ###
> Delete an action.
> > ### Usage: ###
> > `wxamcl.action.delete(actionname|userdatum)`

```lua
         size=wxamcl.action.delete("gossip")
		 size=wacmcl.action.delete(ud)
```
> > The function returns `nil` in case of error, otherwise number of (remaining) defined actions.
> ### wxamcl action enable ###
> > Enable or disable an action.
> > ### Usage: ###
> > `wxamcl.action.enable(actionname|userdatum, true|false)`

```lua
         label = wxamcl.action.enable("gossip", true)
		 label = wxamcl.action.enable(ud, false)
```
> > Returns the label of the action if successful, otherwise `nil`.

