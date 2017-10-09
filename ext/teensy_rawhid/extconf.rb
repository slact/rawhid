require "mkmf"
require "rubygems"

extension_name = "teensy_rawhid"

$srcs = ["#{extension_name}.c"]

case Gem::Platform.local.os
when "linux"
  have_library "usb", nil, ["usb.h"]
  $defs.push "-DOS_LINUX"
  $srcs << "hid_LINUX.c"
#when "darwin"
#  raise "can't build for 
#  have_library "hid", nil, ["hid.h"]
#  $defs.push "-DOS_MACOSX"
else
  raise "Don't know ho to build rawhid on #{Gem::Platform.local.os} yet."
end

create_header
create_makefile "#{extension_name}"
