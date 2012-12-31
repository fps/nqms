# NQMS - The Not Quite Modular Synth

This program is a simple LADSPA host designed to be usable from the commandline without a graphical user interface. It sports a simple readline based interface for loading and connecting plugins. The task of providing the dataflow is realized by using jack ports and connections..

All plugins export all their ports via jack ports which allows patching from the outside if required. 

There is a very simple input language used to define patches. After loading modules every parameter is indexed in numerical form (see the list command below).

## Input language

Strings of the form $PARAMETER  denote a parameter. ${PARAMETER} denotes an optional parameter. $[PARAMETERS] denotes a list of parameters. ${[PARAMETERS]} denotes an optional list of parameters. 

### list

Lists all modules loaded at the current time. The output is of the form

[0] LADSPA '/usr/lib/ladspa/foo.so' 'plugin label'
	[0] 'port name' 'port description' 'jack port name' value
	[1] 'another port name' 'another port description' 'another jack port name'
	...

...


[1] MIDI 

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

> load $FILE_NAME

Clears the current patch and loads a patch from the file $FILE_NAME.

### save

> save [$FILE_NAME]

Saves a patch file to the file $FILE_NAME
