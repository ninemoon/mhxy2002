// by happ@YSZZ
inherit ROOM;

void create ()
{
  set ("short", "鸡窝走道");
  set ("long", @LONG

        你走在鸡窝的走道上，到处都是鸡叫的声音，东面是个[1;32m风景区[m
    可以去散散步，西面有个[1;32mKTV包厢[m。

LONG);

  set("exits", ([ /* sizeof() == 4 */
         "east": __DIR__"fjq",
         "west": __DIR__"ktv",
          "north": __DIR__"road5",
         "south": __DIR__"road7",
]));

        setup();
}
