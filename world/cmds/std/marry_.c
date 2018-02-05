// marry.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object who;
 
	if (!arg) return notify_fail("你要嫁给谁？\n");

	if (me->query("gender")=="男性")
		return notify_fail("只有女人才能答应别人的求婚！\n");

	if (!me->query("proposed"))
		return notify_fail("嗯？没人向你求婚啊。\n");

	if (!objectp(who=present(arg,environment(me))))
		return notify_fail("这里没有这个人。\n");

	if (!who->is_character())
		return notify_fail("想清楚！"+who->name()+"是什么呀！\n");
 
	if (!living(who))
		return notify_fail("嗯...你还是先把"+who->name()+"弄醒吧。\n");
 
 
	message_vision("$N歪头想了会，羞羞答答地说道：好吧！\n",me,who);

	who->delete("proposing");
	who->delete("propose_target");
	who->set("waiting_marry",1);
	who->set("partner", getuid(me));
 

	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : marry <某人>
 
这个指令用来答应别人的求婚，当然你必须是女性，目标必须是正在向你求婚的人。

相关指令请参阅：propose
相关程序请参阅：marriage
 
HELP
    );
    return 1;
}
