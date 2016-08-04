# UE4-RnD
This projects includes most of the things you can find on 
http://www.youtube.com/CAPTNCAPS as a Tutorial.

## Using this Repo
### Windows
Right Click the .uproject file and select "Generate Project Files"  
Loading the project with UE4 should now automatically compile the Project  

### Linux
Go to your UnrealEngine folder and run:  
`$ mono Engine/Binaries/DotNET/UnrealBuildTool.exe -projectfiles -project="/path/to/project/folder/RnD.uproject" -game -engine`  
Exchange -projectfiles with whatever files you need. ( -makefile -cmakefile -kdevelopfile -qmakefile -codelitefile), can use multiple.  
  
Now go into the folder of this repo and run:  
`$ make RnDEditor`  
You should now be able to open the project with Unreal Engine  
If you are not, also run:  
`$ make RnD`

## Adding needed content  
Start the project, go to the root folder (content) and click  
**Add New -> Feature or Content Pack -> Content Packs -> Starter Content**  
You will also need to add AnimStarterPack (UE4 Mannequin), or exchange it for the Blue standard guy that comes with UE4.

## TABLE OF CONTENTS
- Player Character (C++)
- Interaction System (C++)
- Compass
- Lock Picking à la Fallout
- Minimap (defunct/remaking)
- Random Generated World (RGW folder)
- Targeting System
- Camera Switching 
- Character Switching 
- Dialog System (C++/BP)
- Wave System (C++)
