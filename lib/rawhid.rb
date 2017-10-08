require "rawhid/version"
require "teensy_rawhid"

class RawHID
  class RawHIDError
    def initialize(msg, error_code=nil)
      @code = error_code
      super msg
    end
    attr_accessor :code
  end
  private :raw_send, :raw_recv
  
  def write(data, timeout=0)
    if Array === data
      data = data.map(&:chr).join
    end
    ret = raw_send(data, timeout)
    if ret > 0
      ret
    else
      raise RawHIDError.new("Failed sending data", ret)
    end
  end
  
  def read(len, timeout)
    ret = raw_recv(len, timeout)
    if String === data
      return ret
    else
      raise RawHIDError.new("Failed receiving data", ret)
    end
  end
end
