# Fablevirus
(For educational purposes only)A Windows XP virus written in C with a reference to the original Fable video game.


WARNING!!!! COMPILING THIS CODE ON A MACHINE NOT RUNNINING XP CAN STILL CAUSE DAMAGE AND OVERWRITE EXECUTABLE FILES.
ALL EXECUTABLE FILES IN THE DIRECTORY THAT THIS VIRUS IS EXECUTED IN WILL BE OVERWRITTEN WITH THE VIRUS EVEN ON UNIX/LINUX/OR OTHER VERSIONS OF WINDOWS

On Windows XP this virus overwrites the binaries of other executables located in the folder it is run in. The binaries are replaced with the binary of the virus, thus replicating the virus. Within each folder the virus is run, a log is generated of files that have been succesfully infected. The log is saved to a text file.


The virus searches out and finds the start up folder and copies itself there. On computer reboot, virus creates a memory leak that slowly uses all RAM, 
eventually blue screening the computer. As it does this, it prints a cheeky message to a text file on the desktop. The message is a reference to the video game "Fable" and doubles as a log of how much RAM has been consumed.




