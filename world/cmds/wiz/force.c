// haha
// force.c 

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string msg;
        string target;
 
        if (! arg) return notify_fail("��Ҫ˭��ʲô��\n");

        if (sscanf(arg, "%s to %s", target, arg) != 2 ||
            ! objectp(ob = find_player(target)) &&
            ! objectp(ob = present(target, environment(me))) &&
            ! objectp(ob = find_living(target)))
        {
                // û��������󣬲鿴���һ�εĶ���
                if (! objectp(ob = me->query_temp("last_control")))
                        return notify_fail("����û������ˡ�\n");
                if (stringp(target)) arg = target + " " + arg;
        } 
		
        me->set_temp("last_control", ob);
        ob->delete_temp("notify_fail");
        if (! ob->force_me(arg))
        {
                ob->command(arg);
                if (! stringp(msg = ob->query_temp("notify_fail")))
                        msg = ob->name(1) + "�޷�ִ��������\n";
                write(msg);
        }
        return 1;
}

int help(object me)
{
        write( @HELP
ָ���ʽ: force <sb> to do sth.

���ָ�������������һ��������ж��������������������ĳ���ˣ�
��ô�Ժ���Ҫ���������ID��
HELP );
        return 1;
}



