int main(object me, string arg)
{
        string cname,ccmds;
        object ob;
        seteuid(getuid());
        cname = me->query_temp("snoopee");
        if( cname == 0 ) return notify_fail("��û�м����κ��ˡ�\n");
        ob = find_player(cname);
        if( !ob )
                ob = find_living(cname);
        if( !ob )
                return notify_fail("�Ҳ��������������ˡ�\n");
        if( !arg )
        return notify_fail(sprintf("��Ҫ��%s��ʲ���£�\n",ob->name()));
        if( arg == "e" ) arg = "east";
        if( arg == "w" ) arg = "west";
        if( arg == "s" ) arg = "south";
        if( arg == "n" ) arg = "north";
        if( arg == "u" ) arg = "up";
        if( arg == "d" ) arg = "down";
        if( arg == "se" ) arg = "southeast";
        if( arg == "sw" ) arg = "southwest";
        if( arg == "ne" ) arg = "northeast";
        if( arg == "nw" ) arg = "northwest";
        if( arg == "l" ) arg = "look";

        ob->ccommand(arg);

        return 1;
}

int help(object me)
{
   write( @HELP
ָ���ʽ: cmdnpc <commands> �������������˷�����.
HELP
   );
   return 1;
}