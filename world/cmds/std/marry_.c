// marry.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object who;
 
	if (!arg) return notify_fail("��Ҫ�޸�˭��\n");

	if (me->query("gender")=="����")
		return notify_fail("ֻ��Ů�˲��ܴ�Ӧ���˵���飡\n");

	if (!me->query("proposed"))
		return notify_fail("�ţ�û��������鰡��\n");

	if (!objectp(who=present(arg,environment(me))))
		return notify_fail("����û������ˡ�\n");

	if (!who->is_character())
		return notify_fail("�������"+who->name()+"��ʲôѽ��\n");
 
	if (!living(who))
		return notify_fail("��...�㻹���Ȱ�"+who->name()+"Ū�Ѱɡ�\n");
 
 
	message_vision("$N��ͷ���˻ᣬ���ߴ���˵�����ðɣ�\n",me,who);

	who->delete("proposing");
	who->delete("propose_target");
	who->set("waiting_marry",1);
	who->set("partner", getuid(me));
 

	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : marry <ĳ��>
 
���ָ��������Ӧ���˵���飬��Ȼ�������Ů�ԣ�Ŀ��������������������ˡ�

���ָ������ģ�propose
��س�������ģ�marriage
 
HELP
    );
    return 1;
}