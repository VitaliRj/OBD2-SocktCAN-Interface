function blkStruct = slblocks
		% This function specifies that the library should appear
		% in the Library Browser
		% and be cached in the browser repository

		Browser.Library = 'OBD2_SocketCan_Library';
		% 'mylib' is the name of the library

		Browser.Name = 'OBD2 SocketCan Interface';
		% 'My Library' is the library name that appears 
             % in the Library Browser

		blkStruct.Browser = Browser; 