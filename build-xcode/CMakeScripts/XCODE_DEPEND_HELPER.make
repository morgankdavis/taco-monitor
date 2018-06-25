# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.taco_mon.Debug:
/Volumes/Crate/taco-monitor/build-xcode/Debug/taco_mon:
	/bin/rm -f /Volumes/Crate/taco-monitor/build-xcode/Debug/taco_mon


PostBuild.taco_mon.Release:
/Volumes/Crate/taco-monitor/build-xcode/Release/taco_mon:
	/bin/rm -f /Volumes/Crate/taco-monitor/build-xcode/Release/taco_mon


PostBuild.taco_mon.MinSizeRel:
/Volumes/Crate/taco-monitor/build-xcode/MinSizeRel/taco_mon:
	/bin/rm -f /Volumes/Crate/taco-monitor/build-xcode/MinSizeRel/taco_mon


PostBuild.taco_mon.RelWithDebInfo:
/Volumes/Crate/taco-monitor/build-xcode/RelWithDebInfo/taco_mon:
	/bin/rm -f /Volumes/Crate/taco-monitor/build-xcode/RelWithDebInfo/taco_mon




# For each target create a dummy ruleso the target does not have to exist
