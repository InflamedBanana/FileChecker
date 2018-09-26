# FileChecker

A simple file checking console application using c++17 filesystem. It looks in the settings arborescence for non-matching files and logs them out 
( Previously corrected them but it turned out to be a bad idea ).
Settings are set via a json ( rapidjson required to build ) file created at first launch.

### Includes :

- Nomenclature Checking ( prefix, type and name )
- Associated file extension ( e.g. ".meta" files ).
- Extension restriction by directory

### How it works :

1 ) First create settings file by launching the application once. Quit the application afterwards ( Settings Reload in 2.0 )

2 ) Customize the settings -> For the nomenclature settings its kinda obvious but maybe less for the Arborescence.

In the arborescence, a directory corresponds to this :
```
{
  "Name":"../",
  "Exclude_Nomenclature_Check" : false,
  "Exclude_Extension_Check" : false,
  "Exclude_Recursive_Checks" : false,
  "ExtensionRestrict" :
  [],
  "Directories" : 
  []
}
```
The very first directory ( here "../" ) corresponds to the root of the search, relative to the application. Extension restrict is an
array of strings ( ".cpp", ".tga" ... ) and directories an array of directory objects ( same as the one above ). There can be multiple 
root directories ( maybe to check multiple projects ? )

The checker will only look for directories described in the settings, if one does not exist when being checked, it will be created.

3 ) Run the application checks, and Wrong files will be logged in the logged folder.
