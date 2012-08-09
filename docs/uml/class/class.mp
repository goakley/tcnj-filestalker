input metauml;

filenametemplate("%j.mps");

beginfig(1);
  
  Class.Core("Core")
  ("-directory:Tree","-changeLogger:Logger")
  ("+update():void");
  Class.File("File")
  ("-stats:struct stat","-dir:string")
  ("+File(dir:struct directory)","+getPath():int","+getModified():time_t","+getUser():uid_t","+getGroup():gid_t","+getMode():mode_t");
  Class.Logger("Logger")
  ("-logStream:ostream")
  ("+Logger(stream:ostream)","+writeEvent(event:Event):void");
  Class.Event("Event")
  ("-type:EventType","-file:File")
  ("+Event(type:EventType, file:File)","+getType():Type","+getFile():File");
  Class.EventType("EventType")
  ("+Created","+Modified","+Deleted")
  ();
  classStereotypes.EventType("<<enumeration>>");
  Class.UI("UI")
  ()
  ("+getSearch():void","-search(type:EventType, dateStart:time_t, dateEnd:time_t, file:String):LinkedList<File>");

  Note.file("<<FILE>>","All the changes made");
  
  Core.nw = (0, 0);
  File.w = Core.e + (50, 0);
  Logger.n = Core.s - (100, 50);
  Event.w = Logger.e + (50, 0);
  EventType.n = Event.s - (0, 20);
  UI.n = Core.n + (0, 100);
  file.n = Core.n - (150, 0);
  
  drawObjects(Core, File, Logger, Event, EventType, UI, file);

  link(aggregation)(File.w -- Core.e);
  link(associationUni)(EventType.n -- Event.s);
  link(dependency)(Event.n -- Core.s);
  link(dependency)(Event.w -- Logger.e);
  link(associationUni)(Logger.n -- Core.s);
  link(dependency)(File.n -- UI.s);
  link(dependency)(Event.n -- UI.s);
  link(association)(file.s -- Logger.n);
  link(association)(file.n -- UI.s);

endfig;

bye
