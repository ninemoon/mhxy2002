// thousand.c
// by tianlin 2001.5.1

inherit MONEY;

void create()
{
        set_name("[36m一百元人民币[2;37;0m", ({"rmb", "rmb_money"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("money_id", "rmb");
                set("long", "一张面值为一百元的大团结人民币。\n");
                set("unit", "张");
		set("base_value", 100000);
		set("base_unit", "张");
		set("base_weight", 3);
	}
	set_amount(1);
}

