# Introduction #
This section contains the documentation for the client Lua interface.
## Details ##
> You will find here a documentation of all scripting functions.
> Some general stuff:
> > The global lua object is called 'wxamcl'. So all functions are called like wxaml.echo("Test").
> > You can call scriptfunctions directly from the command line:
> > > ?wxamcl.echo("Test text", "red")

> > You can call a whole scriptfile from the command line:
> > > <pre>#script("testscintilla.lua")</pre>

> > If you want to use wxamlc.wait or wxamcl.waitfor to pause the script you need to use the '#tscript' command:
> > > <pre>#tscript("waitfor.lua")</pre>

> > You can call a single function from a file:
> > > <pre>#func("functest.lua", "Test('green', 'red')")</pre>
