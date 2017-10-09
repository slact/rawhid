require "mkmf"
require "rubygems"

extension_name = "teensy_rawhid"

$srcs = ["#{extension_name}.c"]

case Gem::Platform.local.os
when "linux"
  have_library "usb", nil, ["usb.h"]
  $defs.push "-DOS_LINUX"
  $srcs << "hid_LINUX.c"
when "darwin"
  $defs.push "-DOS_MACOSX"
  $srcs << "hid_MACOSX.c"
else
  raise "Don't know ho to build rawhid on #{Gem::Platform.local.os}" yet."
end


create_header
create_makefile "#{extension_name}"
