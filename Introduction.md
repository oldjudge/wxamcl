# Introduction #

wxAmcl is a mud client using wxWidgets 3.2.0.


## Details ##

At the moment there are alpha versions of the client for

  * Windows 10
  * Linux (tested on Linux Mint 21)
  * Mac OSX (more unstable than the other versions)

The client has all features you would expect from a mud client.
Especially it is highly scriptable, using Lua 5.3 as (only) scripting language.
Most of the data files the client uses are lua files and therefore easy to edit.

Scripting allows you to do a lot of things, for example scripting a mapper using lua and GMCP (via the inbuilt event system) for [Aardwolf Mud](http://aardwolf.com).
The event system supports also MSDP protocol, OnConnect, OnDisconnect and OnPacketReceived events.

[Scripting Documentation](ScriptingDocs.md)
