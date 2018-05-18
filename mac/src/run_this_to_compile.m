disp('compiling:');
mex obd2RawJ1979.c obd2RawJ1979_wrapper.c
open('OBD2_SocketCan_Library.slx')
open('Example.slx')