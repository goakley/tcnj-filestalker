input metauml;

filenametemplate("%j.mps");

beginfig(1);

  Actor.User("User");
  Actor.System("File","System");
  Usecase.all("Obtain all output","from file");
  Usecase.obtain("Obtain sorted/filtered","output from file");
  Usecase.filter("Filter output","from file");
  Usecase.cd("Change monitored","directory");
  Usecase.cdout("Change output","file path");
  Usecase.change("Detect file","change");
  Usecase.output("Append to","output file");

  User.n = (0, -150);
  System.n = (300, -100);
  all.n = (100, 0);
  obtain.n = (100, -100);
  filter.n = (200, 0);
  cd.n = (100, -200);
  cdout.n = (100, -300);
  change.n = (200, -100);
  output.n = (200, -200);

  drawObjects(User, System);
  draw objectBox(System.human);
  drawObjects(all, obtain, filter, cd, cdout, change, output);

  link(association)(User.n -- all.w);
  link(association)(User.e -- obtain.w);
  link(association)(obtain.e -- filter.w);
  link(association)(User.e -- cd.w);
  link(association)(User.s -- cdout.w);
  link(associationUni)(change.e -- System.w);
  link(associationUni)(output.e -- System.s);

  draw ((25,25)--(25,-350)--(250, -350)--(250,25)--cycle)
  
endfig;

bye
