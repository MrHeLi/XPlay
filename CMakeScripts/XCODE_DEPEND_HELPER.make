# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.XPlay.Debug:
/Users/heli/CLionProjects/XPlay/Debug/XPlay:
	/bin/rm -f /Users/heli/CLionProjects/XPlay/Debug/XPlay


PostBuild.XPlay.Release:
/Users/heli/CLionProjects/XPlay/Release/XPlay:
	/bin/rm -f /Users/heli/CLionProjects/XPlay/Release/XPlay


PostBuild.XPlay.MinSizeRel:
/Users/heli/CLionProjects/XPlay/MinSizeRel/XPlay:
	/bin/rm -f /Users/heli/CLionProjects/XPlay/MinSizeRel/XPlay


PostBuild.XPlay.RelWithDebInfo:
/Users/heli/CLionProjects/XPlay/RelWithDebInfo/XPlay:
	/bin/rm -f /Users/heli/CLionProjects/XPlay/RelWithDebInfo/XPlay




# For each target create a dummy ruleso the target does not have to exist
