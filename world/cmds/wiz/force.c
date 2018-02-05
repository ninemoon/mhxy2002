// haha
// force.c 

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string msg;
        string target;
 
        if (! arg) return notify_fail("你要谁做什么？\n");

        if (sscanf(arg, "%s to %s", target, arg) != 2 ||
            ! objectp(ob = find_player(target)) &&
            ! objectp(ob = present(target, environment(me))) &&
            ! objectp(ob = find_living(target)))
        {
                // 没有这个对象，查看最后一次的对象
                if (! objectp(ob = me->query_temp("last_control")))
                        return notify_fail("这里没有这个人。\n");
                if (stringp(target)) arg = target + " " + arg;
        } 
		
        me->set_temp("last_control", ob);
        ob->delete_temp("notify_fail");
        if (! ob->force_me(arg))
        {
                ob->command(arg);
                if (! stringp(msg = ob->query_temp("notify_fail")))
                        msg = ob->name(1) + "无法执行你的命令。\n";
                write(msg);
        }
        return 1;
}

int help(object me)
{
        write( @HELP
指令格式: force <sb> to do sth.

这个指令让你控制另外一个人物进行动作，如果你是连续控制某个人，
那么以后不需要在输入这个ID。
HELP );
        return 1;
}



