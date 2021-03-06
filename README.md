# NQMS - The Not Quite Modular Synth

This program is a simple LADSPA host designed to be usable from the commandline without a graphical user interface. It sports a simple readline based interface for loading and connecting plugins. 

There is a very simple input language used to define patches. After loading modules every parameter is indexed in numerical form (see the list command below).

## Input language

Strings of the form $PARAMETER  denote a parameter. ${PARAMETER} denotes an optional parameter. $[PARAMETERS] denotes a list of parameters. ${[PARAMETERS]} denotes an optional list of parameters. 

### list

> list

Lists all modules loaded at the current time. The output is of the form

[0] LADSPA '/usr/lib/ladspa/foo.so' 'plugin label'
	[0] 'port name' 'port description' 'jack port name' value
	[1] 'another port name' 'another port description' 'another jack port name'
	...

...


[1] MIDI 

### list_modules

> list_modules

Lists all available modules on the system.

#### Notes:

* Jack port names are unique.

* See the polyphony command below for how polyphony works.

### add

Adds a module. The command is of the form:

add $TYPE [$PARAMETERS]

#### Types:

##### LADSPA

> add ladspa {$LIBRARY_FILE} $NAME

The [$PARAMETERS] are 



##### MIDI

> add midi

Adds a midi input and output port to the patch. 

### remove

> remove $INDEX

Removes the module with index $INDEX from the patch.

### polyphony 

> polyphony $NUMBER_OF_VOICES

Sets the polyphony of the patch. TODO: Details of voice allocation (oldest goes first..)

### connect

> connect $SOURCE_PORT $TARGET_PORT

Establishes connections between modules.

### load

> load [$FILE_NAME]

Clears the current patch and loads a patch from the file $FILE_NAME. If $FILE_NAME is omitted the last used file name is used.

### save

> save [$FILE_NAME]

Saves a patch file to the file $FILE_NAME. If $FILE_NAME is not specified the last used file name is used.
=======
nqms
====

The not quite modular synth - a simple modular synth with a readline interface
