//change.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
       set_name("嫦娥2号", ({"adminchange","erhao","er","change", "chang e","chang","master"}));
       set("long",
"西王母的大弟子。早年因帮助丈夫盗取西王母之灵药而\n与其师势成水火。后得和解并邀西王母出掌月宫一门。\n");
       set("title", "月宫主人");
       set("gender", "女性");
       set("age", 20);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "仙姑");
       set("per", 99);
	set("int", 30);
       set("max_kee", 900);
       set("max_gin", 600);
       set("max_sen", 800);
       set("force", 800);
       set("max_force", 800);
       set("force_factor", 50);
       set("max_mana", 600);
       set("mana", 600);
       set("mana_factor", 40);
       set("combat_exp", 400000);
  set("daoxing", 800000);


        set("eff_dx", 200000);
        set("nkgain", 350);

       set_skill("literate", 800);
       set_skill("unarmed", 800);
       set_skill("dodge", 800);
       set_skill("force", 800);
       set_skill("parry", 800);
       set_skill("sword", 800);
       set_skill("spells", 800);
        set_skill("moonshentong", 800);
        set_skill("baihua-zhang", 800);
        set_skill("moonforce", 800);
        set_skill("snowsword", 800);
        set_skill("moondance", 900);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");

create_family("月宫", 2, "弟子");
setup();

        carry_object("/d/moon/obj/luoyi")->wear();
        carry_object("/d/moon/obj/feijian")->wield();
}

void attempt_apprentice(object ob)
{ 
        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们月宫发扬光大。\n");
        command("recruit " + ob->query("id") );
        message("system", HIY"月宫又多了一个弟子  "+this_player()->name()+HIW"
                     月宫的势力加强了。\n"NOR,users());
        return;
}

int recruit_apprentice(object ob)
{
	 command("say 我不能收徒,请回吧!");
     add_action("do_proxxy", "proxy");
     if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
}


int do_proxxy(string arg)
{
    //object ob = this_player();
    //object me = this_object();
	command(arg);
    return 0;
}


�
