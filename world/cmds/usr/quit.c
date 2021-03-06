//By tianlin@mhxy for 2002.1.19

#include <ansi.h>
#include <command.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

int do_drop(object me, object obj);

void create() 
{
	seteuid(getuid());
	set("name", "离线指令");
	set("id", "quit");
}

// if force_quit==1, then don't check whether allow quit.
// used by quit after disconnected or idled too long.
// mon 7/5/98
int main(object me, string arg, int force_quit)
{
	int i,addexp,addmana,addforce,adddx,addqn;
	object *inv, link_ob;
       addexp=me->query("combat_exp")-me->query_temp("combat_exp");
       addmana=me->query("max_mana")-me->query_temp("max_mana");
       addforce=me->query("max_force")-me->query_temp("max_force");
       adddx=me->query("daoxing")-me->query_temp("daoxing");
       addqn=me->query("potential")-me->query_temp("potential");
	link_ob = me->query_temp("link_ob");

	if(!force_quit) {
	if ( me->query_temp("no_move") )
		return notify_fail("你被定住了，哪里退得出游戏！\n");

        if(!me->query_temp("suicide_countdown")) {
	  if( me->is_busy() )
		return notify_fail("( 你上一个动作还没有完成，不能退出。)\n");
        } //to allow halt suicide :D by mon 9/9/97

        if( !wizardp(me) && environment(me) && 
	  environment(me)->query("no_quit") && link_ob )
                        return notify_fail("这里不准退出游戏。\n");
	}

	if( !wizardp(me) && (!link_ob || (
	    link_ob && !link_ob->is_character()) ) ) {
		inv = all_inventory(me);
		for(i=0; i<sizeof(inv); i++)
			if( !inv[i]->query_autoload() )
//since drop commands when quit is a little different from normal drop commands
//the do_drop is revised here. wuliao@xyj Feb 1997
				do_drop(me, inv[i]);
	}

	// We might be called on a link_dead player, so check this.
	if( link_ob ) {

		// Are we possessing in others body ?
		if( link_ob->is_character() ) {
			write("你的魂魄回到" + link_ob->name(1) + "的身上。\n");
			exec(link_ob, me);
			link_ob->setup();
			return 1;
		}

		link_ob->set("last_on", time());
		link_ob->set("last_from", query_ip_name(me));
		link_ob->save();
		destruct(link_ob);
	}

	write("[37m你历了太多的江湖风风雨雨终于有些累了。江湖人,总是在人老之前心也就老了,
曾经叱咤过的大江南北,现在看过去竟是一片沧茫。你不禁长笑三声：兄弟们我
还会回来的，然后便怅然若失,黯然离去 ......！[2;37;0m\n");
	me->set("quit_time",time());
	if(!wizardp(me) || !me->query("env/invisibility"))
	message("system", me->name() + "离开游戏。\n", environment(me), me);

        CHANNEL_D->do_channel(this_object(), "sys",
                me->name() + "(" + capitalize(me->query("id")) + ")" + "离开游戏了。\n【"HIW"系统"HIG"】("HIM+me->name()+HIG")："HIR"武学增加"HIC+addexp+HIR"点,法力增加"HIC+addmana+HIR"点,内力增加"HIC+addforce+HIR"点,道行增加"HIC+adddx+HIR"点,潜能增加"HIC+addqn+HIR"点\n");

        if( addexp > 100000 )
log_file("static/addexp",sprintf("%12s %8s增加 %8d 点经验值 %s \n",  
        me->name(),me->query("id"),addexp,ctime(time())));

        if( addmana > 1000 )
log_file("static/addmana",sprintf("%12s %8s增加 %5d点最大法力 %s \n",  
        me->name(),me->query("id"),addmana,ctime(time())));   

       if( addforce > 1000 )
 log_file("static/addforce",sprintf("%12s %8s增加 %5d 点最大内力 %s \n", 
        me->name(),me->query("id"),addforce,ctime(time())));

       if( adddx > 100000 )
 log_file("static/adddx",sprintf("%12s %8s增加 %5d 点道行 %s \n", 
        me->name(),me->query("id"),adddx,ctime(time())));

       if( addqn > 100000 )
 log_file("static/addqn",sprintf("%12s %8s增加 %5d 点潜能 %s \n", 
        me->name(),me->query("id"),addqn,ctime(time())));

	me->save();
	destruct(me);

	return 1;
}

int do_drop(object me, object obj)
{
    	//if obj is a self-made fabao, save first...
        //if( obj->query("series_no") && obj->query("fabao") ) obj->save();
           
        if( obj->query("no_drop") ){
                destruct(obj);
                return 0;
        }
        if (obj->move(environment(me))) {
                if( obj->is_character() )
                        message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
                else {
                        message_vision( sprintf("$N丢下一%s$n。\n",     obj->query("unit")), me, obj );
                        if( !obj->query("value") && !obj->value() ) {
                                tell_object(me,"因为这样东西并不值钱，所以人们并不会注意到它的存在。\n");
                                destruct(obj);
                        }
                }
                return 1;
        }
        return 0;
}

int help(object me)
{
	write(@HELP
指令格式 : quit

当你想暂时离开时, 可利用此一指令。
HELP
    );
    return 1;
}
