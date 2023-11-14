#ifndef __KLCFSM_H__
#define __KLCFSM_H__

enum _KLEM_FSMSTATUS
{
	F_NONE,
	F_INIT,
	F_UPDATE,
	F_RELEASE
};

#define KLEM_FSMSTATUS enum _KLEM_FSMSTATUS

#endif // !__KLCFSM_H__
