# from syndesi.commands import Commands
#from struct import pack, unpack
from construct import Struct, Int16ub, Int16ul, this, Byte, Array


from syndesi.frame_contents import FrameContent, FRAME_ENDIAN, frames_match, Commands_IDs

class Frame():
    format = Struct (
        "length" / Int16ub if FRAME_ENDIAN == 'big' else Int16ul,
        "command" / Int16ub if FRAME_ENDIAN == 'big' else Int16ul,
        "content" / Array(this.length - 2, Byte)
    )
    def __init__(self):
        """
        Frame instance
        """
        pass
    
    def parse(self, buffer : bytearray):
        """
        Create a frame from a received buffer

        Parameters
        ----------
        buffer : bytearray

        Returns
        -------
        frameContent : FrameContent
        """
        length, command, content = self.format.parse(buffer)

        # Check if the frame is OK
        if length == len(content) + 2:
            # Ok
            pass
        else:
            print(f"Frame size is invalid : {len(content) + 2} instead of {length}")
        frameContent : FrameContent = frames_match[command]()

        frameContent.parse(content)

        return frameContent

    def value(self, content : FrameContent):
        """        
        Returns value of a frame as a bytearray

        Returns
        -------
        output : bytearray
        """
        content_array = content.value()

        output = self.format.build(dict(length = len(content_array) + 2, command = content.command_ID, content = content_array))

        return output

    