//By angela@mhxy 2001.12.29
// jingheal.c

#include <ansi.h>

int exert(object me, object target)
{
	if( me->is_fighting() )
		return notify_fail("ս�����˹����ˣ�������\n");

	if( (int)me->query("force") < 50 )
		return notify_fail("�������������\n");

	if( (int)me->query("eff_sen") < (int)me->query("max_sen") / 2 )
		return notify_fail("�㾫��ʵ�ڲ��ã�ֻ��һ���ڹ���������Σ�գ�\n");

message_vision(
HIW "$N����������������ķ������˲��ã�$N����������Ө����ɫ����������������͸���ഺ����Ϣ��\n" NOR,
	me );

	me->receive_curing("sen", 10 + (int)me->query_skill("spells")/2 );
	me->add("force", -30);

	return 1;
}