// suicide.c
// By tianlin 2001.5.8
// 加入自杀先要输入身份标识

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( me->is_busy() )
		return notify_fail("你上一个动作还没完成。\n");

	if( !arg ) {
		write("你重新投胎。\n");
		return 1;
	}

	if( arg!="-f" ) 
		return notify_fail("自杀有两种，您是要永远死掉还是重新投胎？\n");

	if(wizardp(me))
	    return notify_fail("请不要自杀掉巫师帐号，谢谢！\n");

	write(
		"如果您选择永远死掉的自杀方式，这个人物的资料就永远删除了，请务必\n"
		"考虑清楚，确定的话请输入您的"BLINK HIW"身份标识：\n"NOR);
	CHANNEL_D->do_channel(this_object(),"rumor",me->name()+"正在寻找一种逃避烦恼的方法。");
	input_to("check_superpasswd", 1, me, 1);
	return 1;
}
// by tianlin 2001.5.8
private void check_superpasswd(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("superpasswd");
	if( crypt(passwd, old_pass)!=old_pass ) {
              write("\n身份标识错误！\n");
              return;
       }
       write("请输入您的密码：");
       input_to("check_password", 1, me, 1);
}
private void check_password(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("password");
	if( crypt(passwd, old_pass)!=old_pass ) {
		write("密码错误！\n");
		return;
	}

	if (forever) {
		tell_object( me,
			HIR "\n\n你决定要自杀了，如果三十秒钟内不后悔，就真的永别了。\n\n\n" NOR);
		me->set_temp("suicide_countdown", 30);
		me->start_busy( (: call_other, this_object(), "slow_suicide" :) );
	}
}

private int slow_suicide(object me)
{
	object link_ob;
	int stage;
	string myid, couple;

	stage = me->query_temp("suicide_countdown");
	me->add_temp("suicide_countdown", -1);
	if( stage > 1 ) {
		if( stage%5 == 0 )
		  tell_object(me, 
			HIR "你还有 " + stage + " 秒的时间可以后悔。"+
			"(用quit命令来后悔)\n" NOR);
		return 1;
	}

	link_ob = me->query_temp("link_ob");
	if( !link_ob ) return 0;

	log_file("static/SUICIDE",
		sprintf("%s(%s) commits a suicide on %s from %s\n", geteuid(me), me->name(), ctime(time()), (string)query_ip_name(me) ) );

	seteuid(getuid());
	rm( link_ob->query_save_file() + __SAVE_EXTENSION__ );
	rm( me->query_save_file() + __SAVE_EXTENSION__ );
	myid=me->query("id");

	// remove player home.
	rm( "/data/playerhomes/h_"+myid+ __SAVE_EXTENSION__ );

	// remove mailbox.
	rm( "/data/mail/"+myid[0..0]+"/"+myid+ __SAVE_EXTENSION__ );

	// remove couple's home as well. (the home is registered by the 
	// couple.)
	couple=me->query("coupld/id");
	if(couple)
	  rm("/data/mail/"+couple[0..0]+"/"+couple+__SAVE_EXTENSION__);


	write("好吧，永别了:(\n");
	tell_room(environment(me), me->name() +
		"自杀了，以后你再也看不到这个人了。\n", ({me}));
	CHANNEL_D->do_channel(this_object(),"rumor",me->name()+"为了逃避尘世间的烦恼，提前自我解放了。");
	destruct(me);
	return 0;
}
int halt_suicide(object me)
{
	tell_object(me, "你放弃了自杀的念头。\n");
	CHANNEL_D->do_channel(this_object(),"rumor",me->name(1) + "决定继续勇敢地活下去。");
	return 1;
}

int help (object me)
{
        write(@HELP
指令格式: suicide [-f]
 
如果因为某种原因你不想活了, 你可以选择自杀.
自杀分两种:
[1;31m注: 因为有的玩家把自己的人给别人挂机,而别人却给自杀了,
一类等等,请不要轻易把身份标识告诉别人,如发生以外,
巫师一律不付任何责任.[2;37;0m
 
suicide    : 重新投胎
suicide -f : 永远的除去玩家资料, 系统会要求你
             输入密码以及身份标识以确认身份.
 
请慎重选择 :)
 
HELP
);
        return 1;
}
