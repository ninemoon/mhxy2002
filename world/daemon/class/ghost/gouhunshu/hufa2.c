// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// invocation.c

inherit SSERVER;

int cast(object me, object target)
{   
        int invocation_time;
        object soldier;

        if( !me->is_fighting() )
                 notify_fail("����û����Ҫɱ�㣡\n");
   
		if((string)me->query("family/family_name")!="���޵ظ�")
                notify_fail("�㲻�����޵ظ��ĵ��� \n"); 
			 
        message_vision("$N�૵����˼������\n", me);

        me->add("mana", -50);
        me->receive_damage("sen", 40);

        seteuid(getuid());
        soldier = new("/d/death/npc/hufa");
        soldier->move(environment(me));
        soldier->invocation(me);  
		
        return 8+random(5);
}
