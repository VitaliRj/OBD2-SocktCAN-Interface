uiopen('OBD2_SocketCan_Library.slx',1)

set_param(gcs,'EnableLBRepository','on');

ann = find_system('OBD2_SocketCan_Library','findall','on','RegExp',...
'on','Type','annotation','Name','annotation');

set_param(ann,'Description',...
'Use this annotation to label the model.');