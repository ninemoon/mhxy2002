//change.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
       set_name("æÏ¶ð2ºÅ", ({"adminchange","erhao","er","change", "chang e","chang","master"}));
       set("long",
"Î÷ÍõÄ¸µÄ´óµÜ×Ó¡£ÔçÄêÒò°ïÖúÕÉ·òµÁÈ¡Î÷ÍõÄ¸Ö®ÁéÒ©¶ø\nÓëÆäÊ¦ÊÆ³ÉË®»ð¡£ºóµÃºÍ½â²¢ÑûÎ÷ÍõÄ¸³öÕÆÔÂ¹¬Ò»ÃÅ¡£\n");
       set("title", "ÔÂ¹¬Ö÷ÈË");
       set("gender", "Å®ÐÔ");
       set("age", 20);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "ÏÉ¹Ã");
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

create_family("ÔÂ¹¬", 2, "µÜ×Ó");
setup();

        carry_object("/d/moon/obj/luoyi")->wear();
        carry_object("/d/moon/obj/feijian")->wield();
}

void attempt_apprentice(object ob)
{ 
        command("pat "+ob->query("id"));
        command("say ºÃ£¬Ï£Íû" + RANK_D->query_respect(ob) +
"¶à¼ÓÅ¬Á¦£¬°ÑÎÒÃÇÔÂ¹¬·¢Ñï¹â´ó¡£\n");
        command("recruit " + ob->query("id") );
        message("system", HIY"ÔÂ¹¬ÓÖ¶àÁËÒ»¸öµÜ×Ó  "+this_player()->name()+HIW"
                     ÔÂ¹¬µÄÊÆÁ¦¼ÓÇ¿ÁË¡£\n"NOR,users());
        return;
}

int recruit_apprentice(object ob)
{
	 command("say ÎÒ²»ÄÜÊÕÍ½,Çë»Ø°É!");
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


ÿ
