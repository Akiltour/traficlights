//This file was generated from (Academic) UPPAAL 4.1.4 (rev. 5648), July 2014

/*

*/
control:A [ Process.AC_T U not(Process.off1)]

/*

*/
control:A [ Process.off1 U not(Process.BD)]

/*

*/
control:A [ Process.off1 U not(Process.AC)]

/*

*/
E<> Process.BD_T

/*

*/
E<> Process.BD_B_T

/*

*/
E<> Process.BD_B

/*

*/
E<> Process.AC_B_T

/*

*/
E<> Process.AC_B

/*

*/
E<> Process.off2

/*

*/
E<> Process.AC_T

/*

*/
E<> Process.AC

/*

*/
E<> Process.BD

/*

*/
A<> Process.AC_T

/*

*/
A[] not deadlock
