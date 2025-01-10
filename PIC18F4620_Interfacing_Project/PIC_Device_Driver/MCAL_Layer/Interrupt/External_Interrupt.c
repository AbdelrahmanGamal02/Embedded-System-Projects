/* 
 * File:   External_Interrupt.c
 * Author: abdo
 *
 * Created on April 13, 2024, 11:15 PM
 */

#include "External_Interrupt.h"

/***************** Helper Functions for INTx interrupt ****************/

static Interrupt_Handler INT0_Interrupt_Handler = NULL;
static Interrupt_Handler INT1_Interrupt_Handler = NULL;
static Interrupt_Handler INT2_Interrupt_Handler = NULL;

static Std_ReturnType Ext_Interrupt_INT0_SETHandler(void (* Interrupt_Handler) (void));
static Std_ReturnType Ext_Interrupt_INT1_SETHandler(void (* Interrupt_Handler) (void));
static Std_ReturnType Ext_Interrupt_INT2_SETHandler(void (* Interrupt_Handler) (void));

static Std_ReturnType Ext_Interrupt_INTx_SETHandler(const EXTInterrupt_INTx_Type* Int_Obj);


static Std_ReturnType Ext_Interrupt_INTx_Enable_And_Priority(const EXTInterrupt_INTx_Type* Int_Obj);
static Std_ReturnType Ext_Interrupt_INTx_Disable(const EXTInterrupt_INTx_Type* Int_Obj);
static Std_ReturnType Ext_Interrupt_INTx_Edge_Selection(const EXTInterrupt_INTx_Type* Int_Obj);
static Std_ReturnType Ext_Interrupt_INTx_Pin_Init(const EXTInterrupt_INTx_Type* Int_Obj);
static Std_ReturnType Ext_Interrupt_INTx_Clear_Flag(const EXTInterrupt_INTx_Type* Int_Obj);

/***************************************************/
/***************** Helper Functions for PORTB Onchange interrupt ****************/

/******** it is an interrupt handler when voltage change from HIGH to LOW ********/
static Interrupt_Handler RB4_Interrupt_Handler_Low = NULL;
static Interrupt_Handler RB5_Interrupt_Handler_Low = NULL;
static Interrupt_Handler RB6_Interrupt_Handler_Low = NULL;
static Interrupt_Handler RB7_Interrupt_Handler_Low = NULL;
/**********************************************************************************/
/******** it is an interrupt handler when voltage change from LOW to HIGH ********/
static Interrupt_Handler RB4_Interrupt_Handler_High = NULL;
static Interrupt_Handler RB5_Interrupt_Handler_High = NULL;
static Interrupt_Handler RB6_Interrupt_Handler_High = NULL;
static Interrupt_Handler RB7_Interrupt_Handler_High = NULL;
/**********************************************************************************/

static Std_ReturnType Ext_Interrupt_RB4_SETHandler(void (* Interrupt_Handler_Low) (void) , void (* Interrupt_Handler_High) (void));
static Std_ReturnType Ext_Interrupt_RB5_SETHandler(void (* Interrupt_Handler_Low) (void) , void (* Interrupt_Handler_High) (void));
static Std_ReturnType Ext_Interrupt_RB6_SETHandler(void (* Interrupt_Handler_Low) (void) , void (* Interrupt_Handler_High) (void));
static Std_ReturnType Ext_Interrupt_RB7_SETHandler(void (* Interrupt_Handler_Low) (void) , void (* Interrupt_Handler_High) (void));

static Std_ReturnType Ext_Interrupt_RBx_SETHandler(const EXTInterrupt_PBx_Type* Int_Obj);

static Std_ReturnType Ext_Interrupt_RBx_Enable_and_Priority(const EXTInterrupt_PBx_Type* Int_Obj);
static Std_ReturnType Ext_Interrupt_RBx_Pin_Init(const EXTInterrupt_PBx_Type* Int_Obj);


/***************************************************/


/***************** Functions for INTx interrupt ****************/
Std_ReturnType Ext_Interrupt_INTx_Initilization(const EXTInterrupt_INTx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Interrupt */
        ret_state = Ext_Interrupt_INTx_Disable(Int_Obj);
        /* Clear Interrupt Flag */
        ret_state &= Ext_Interrupt_INTx_Clear_Flag(Int_Obj);
        /* Adjust edge select bit  */
        ret_state &= Ext_Interrupt_INTx_Edge_Selection(Int_Obj);
        /* Adjust callback function */
        ret_state &= Ext_Interrupt_INTx_SETHandler(Int_Obj);
        /* initialize interrupt pins */
        ret_state &= Ext_Interrupt_INTx_Pin_Init(Int_Obj);
        /* Enable Interrupt */
        ret_state &= Ext_Interrupt_INTx_Enable_And_Priority(Int_Obj);
        
    }
    
    return ret_state;
}

Std_ReturnType Ext_Interrupt_INTx_deInitilization(const EXTInterrupt_INTx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = Ext_Interrupt_INTx_Disable(Int_Obj);
    }
    
    return ret_state;
}
/***************************************************/
/************** INTx ISR Services ***********************/
void INT0_ISR(void)
{
    /******* Clear Flag ************/
    Ext_INT0_INTERRUPT_Clear_FLAG();
    
    /******* Code  ******/
    
    /****callback function *********/
    if(INT0_Interrupt_Handler)
    {
        INT0_Interrupt_Handler();
    }
}

void INT1_ISR(void)
{
    /******* Clear Flag ************/
    Ext_INT1_INTERRUPT_Clear_FLAG();
    
    /******* Code  ******/
    
    /****callback function *********/
    if(INT1_Interrupt_Handler)
    {
        INT1_Interrupt_Handler();
    }
}

void INT2_ISR(void)
{
    /******* Clear Flag ************/
    Ext_INT2_INTERRUPT_Clear_FLAG();
    
    /******* Code  ******/
    
    /****callback function *********/
    if(INT2_Interrupt_Handler)
    {
        INT2_Interrupt_Handler();
    }
}

/***************************************************/
/***************** Functions for PORTB Onchange interrupt ****************/
Std_ReturnType Ext_Interrupt_PBx_Initilization(const EXTInterrupt_PBx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        /* Disable Interrupt */
        Ext_PORTB_onChange_INTERRUPT_DISABLE();
        /* Clear Interrupt Flag */
        Ext_PORTB_onChange_INTERRUPT_Clear_FLAG();
        /* Adjust callback function */
        ret_state = Ext_Interrupt_RBx_SETHandler(Int_Obj);
        /* initialize interrupt pins */
        ret_state &= Ext_Interrupt_RBx_Pin_Init(Int_Obj);
        /* Enable Interrupt */
        ret_state &= Ext_Interrupt_RBx_Enable_and_Priority(Int_Obj);
    }
    
    return ret_state;
}

Std_ReturnType Ext_Interrupt_PBx_deInitilization(const EXTInterrupt_PBx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        Ext_PORTB_onChange_INTERRUPT_DISABLE();
        Ext_PORTB_onChange_INTERRUPT_Clear_FLAG();
        ret_state = Func_OK;
    }
    
    return ret_state;
}
/***************************************************************/
/************** RBx ISR Services ***********************/

void RB4_ISR(uint8 RB4_Source)
{
    /******* Clear Flag ************/
    Ext_PORTB_onChange_INTERRUPT_Clear_FLAG();
    
    /******* Code  ******/
    
    /****callback function *********/
    if(RBx_Interrupt_High_Rising == RB4_Source)
    {
        if(RB4_Interrupt_Handler_High) { RB4_Interrupt_Handler_High(); }
    }
    else if(RBx_Interrupt_Low_Falling == RB4_Source)
    {
        if(RB4_Interrupt_Handler_Low) { RB4_Interrupt_Handler_Low(); }
    }
}

void RB5_ISR(uint8 RB5_Source)
{
    Ext_PORTB_onChange_INTERRUPT_Clear_FLAG();
    
    /******* Code  ******/
    
    /****callback function *********/
    if(RBx_Interrupt_High_Rising == RB5_Source)
    {
        if(RB5_Interrupt_Handler_High) { RB5_Interrupt_Handler_High(); }
    }
    else if(RBx_Interrupt_Low_Falling == RB5_Source)
    {
        if(RB5_Interrupt_Handler_Low) { RB5_Interrupt_Handler_Low(); }
    }
}

void RB6_ISR(uint8 RB6_Source)
{
    Ext_PORTB_onChange_INTERRUPT_Clear_FLAG();
    
    /******* Code  ******/
    
    /****callback function *********/
    if(RBx_Interrupt_High_Rising == RB6_Source)
    {
        if(RB6_Interrupt_Handler_High) { RB6_Interrupt_Handler_High(); }
    }
    else if(RBx_Interrupt_Low_Falling == RB6_Source)
    {
        if(RB6_Interrupt_Handler_Low) { RB6_Interrupt_Handler_Low(); }
    }
}

void RB7_ISR(uint8 RB7_Source)
{
    Ext_PORTB_onChange_INTERRUPT_Clear_FLAG();
    
    /******* Code  ******/
    
    /****callback function *********/
    if(RBx_Interrupt_High_Rising == RB7_Source)
    {
        if(RB7_Interrupt_Handler_High) { RB7_Interrupt_Handler_High(); }
    }
    else if(RBx_Interrupt_Low_Falling == RB7_Source)
    {
        if(RB7_Interrupt_Handler_Low) { RB7_Interrupt_Handler_Low(); }
    }
}


/***************************************************/


/* Implementation of Helper Function of INTx */
static Std_ReturnType Ext_Interrupt_INTx_Enable_And_Priority(const EXTInterrupt_INTx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        switch(Int_Obj->Source)
        {
            case EXTINTERRUPT_INT0 :
            {
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
            INTERRUPT_PRIORTY_LEVELS_ENABLE();
            INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
#else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_Preipheral_INTERRUPT_ENABLE(); 
#endif
                Ext_INT0_INTERRUPT_ENABLE();
                ret_state = Func_OK;
                break;
            }
            case EXTINTERRUPT_INT1 :
            {
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
            INTERRUPT_PRIORTY_LEVELS_ENABLE();
            if(INTERRUPT_LOW_PRIORITY == Int_Obj->Priority)
                {
                    INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
                    Ext_INT1_INTERRUPT_LOW_Priority();
                }
                else if(INTERRUPT_HIGH_PRIORITY == Int_Obj->Priority)
                {
                    INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
                    Ext_INT1_INTERRUPT_High_Priority();
                }
                else { /* NoThing */ }
            
#else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_Preipheral_INTERRUPT_ENABLE(); 
#endif
                Ext_INT1_INTERRUPT_ENABLE();
                ret_state = Func_OK;
                break;
            }
            case EXTINTERRUPT_INT2 :
            {
#if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
            INTERRUPT_PRIORTY_LEVELS_ENABLE();
            if(INTERRUPT_LOW_PRIORITY == Int_Obj->Priority)
                {
                    INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
                    Ext_INT2_INTERRUPT_LOW_Priority();
                }
                else if(INTERRUPT_HIGH_PRIORITY == Int_Obj->Priority)
                {
                    INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
                    Ext_INT2_INTERRUPT_High_Priority();
                }
                else { /* NoThing */ }
#else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_Preipheral_INTERRUPT_ENABLE(); 
#endif
                Ext_INT2_INTERRUPT_ENABLE();
                ret_state = Func_OK;
                break;
            }
            default : ret_state = Func_Not_OK;
        }
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_INTx_Disable(const EXTInterrupt_INTx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        switch(Int_Obj->Source)
        {
            case EXTINTERRUPT_INT0 :
            {
                Ext_INT0_INTERRUPT_DISABLE();
                ret_state = Func_OK;
                break;
            }
            case EXTINTERRUPT_INT1 :
            {
                Ext_INT1_INTERRUPT_DISABLE();
                ret_state = Func_OK;
                break;
            }
            case EXTINTERRUPT_INT2 :
            {
                Ext_INT2_INTERRUPT_DISABLE();
                ret_state = Func_OK;
                break;
            }
            default : ret_state = Func_Not_OK;
        }
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_INTx_Edge_Selection(const EXTInterrupt_INTx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        switch(Int_Obj->Source)
        {
            case EXTINTERRUPT_INT0 :
            {
                if(INTERRUPT_FALLING_Edge == Int_Obj->Edge)
                {
                    Ext_INT0_INTERRUPT_Falling_Edge_Select();
                }
                else
                {
                    Ext_INT0_INTERRUPT_Rising_Edge_Select();
                }
              
                ret_state = Func_OK;
                break;
            }
            case EXTINTERRUPT_INT1 :
            {
                if(INTERRUPT_FALLING_Edge == Int_Obj->Edge)
                {
                    Ext_INT1_INTERRUPT_Falling_Edge_Select();
                }
                else
                {
                    Ext_INT1_INTERRUPT_Rising_Edge_Select();
                }
                ret_state = Func_OK;
                break;
            }
            case EXTINTERRUPT_INT2 :
            {
                if(INTERRUPT_FALLING_Edge == Int_Obj->Edge)
                {
                    Ext_INT2_INTERRUPT_Falling_Edge_Select();
                }
                else
                {
                    Ext_INT2_INTERRUPT_Rising_Edge_Select();
                }
                ret_state = Func_OK;
                break;
            }
            default : ret_state = Func_Not_OK;
        }
    }
    
    return ret_state;
}


static Std_ReturnType Ext_Interrupt_INTx_Pin_Init(const EXTInterrupt_INTx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Direction_Initilization(&(Int_Obj->Interrupt_Pins));
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_INTx_Clear_Flag(const EXTInterrupt_INTx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        switch(Int_Obj->Source)
        {
            case EXTINTERRUPT_INT0 :
            {
                Ext_INT0_INTERRUPT_Clear_FLAG();
                ret_state = Func_OK;
                break;
            }
            case EXTINTERRUPT_INT1 :
            {
                Ext_INT1_INTERRUPT_Clear_FLAG();
                ret_state = Func_OK;
                break;
            }
            case EXTINTERRUPT_INT2 :
            {
                Ext_INT2_INTERRUPT_Clear_FLAG();
                ret_state = Func_OK;
                break;
            }
            default : ret_state = Func_Not_OK;
        }
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_INT0_SETHandler(void (* Interrupt_Handler) (void))
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Interrupt_Handler)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        INT0_Interrupt_Handler = Interrupt_Handler;
        ret_state = Func_OK;
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_INT1_SETHandler(void (* Interrupt_Handler) (void))
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Interrupt_Handler)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        INT1_Interrupt_Handler = Interrupt_Handler;
        ret_state = Func_OK;
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_INT2_SETHandler(void (* Interrupt_Handler) (void))
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Interrupt_Handler)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        INT2_Interrupt_Handler = Interrupt_Handler;
        ret_state = Func_OK;
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_INTx_SETHandler(const EXTInterrupt_INTx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        switch(Int_Obj->Source)
        {
            case EXTINTERRUPT_INT0 :
            {
                ret_state = Ext_Interrupt_INT0_SETHandler(Int_Obj->Ext_Interrupt_Handler);
                break;
            }
            case EXTINTERRUPT_INT1 :
            {
                ret_state = Ext_Interrupt_INT1_SETHandler(Int_Obj->Ext_Interrupt_Handler);
                break;
            }
            case EXTINTERRUPT_INT2 :
            {
                ret_state = Ext_Interrupt_INT2_SETHandler(Int_Obj->Ext_Interrupt_Handler);
                break;
            }
            default : ret_state = Func_Not_OK;
        }
    }
    
    return ret_state;
}

/*************************************************************/

/* Implementation of Helper Function of RBx */

static Std_ReturnType Ext_Interrupt_RBx_Enable_and_Priority(const EXTInterrupt_PBx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        #if INTERRUPT_PRIORITY_LEVELS == PRIORITY_FEATURE_ENABLE
            INTERRUPT_PRIORTY_LEVELS_ENABLE();
            if(INTERRUPT_LOW_PRIORITY == Int_Obj->Priority)
            {
                INTERRUPT_LOW_PRIORTY_INTERRUPT_ENABLE();
                Ext_PORTB_onChange_LOW_Priority();
            }
            else if(INTERRUPT_HIGH_PRIORITY == Int_Obj->Priority)
            {
                INTERRUPT_HIGH_PRIORTY_INTERRUPT_ENABLE();
                Ext_PORTB_onChange_High_Priority();
            }
            else{ /* NoThing */}

        #else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_Preipheral_INTERRUPT_ENABLE(); 
        #endif

        Ext_PORTB_onChange_INTERRUPT_ENABLE();
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_RBx_Pin_Init(const EXTInterrupt_PBx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        ret_state = GPIO_Pin_Direction_Initilization(&(Int_Obj->Interrupt_Pins));
    }
    
    return ret_state;
}


static Std_ReturnType Ext_Interrupt_RB4_SETHandler(void (* Interrupt_Handler_Low) (void) , void (* Interrupt_Handler_High) (void))
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == Interrupt_Handler_Low) || (NULL == Interrupt_Handler_High))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        RB4_Interrupt_Handler_Low = Interrupt_Handler_Low;
        RB4_Interrupt_Handler_High = Interrupt_Handler_High;
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_RB5_SETHandler(void (* Interrupt_Handler_Low) (void) , void (* Interrupt_Handler_High) (void))
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == Interrupt_Handler_Low) || (NULL == Interrupt_Handler_High))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        RB5_Interrupt_Handler_Low = Interrupt_Handler_Low;
        RB5_Interrupt_Handler_High = Interrupt_Handler_High;
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_RB6_SETHandler(void (* Interrupt_Handler_Low) (void) , void (* Interrupt_Handler_High) (void))
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == Interrupt_Handler_Low) || (NULL == Interrupt_Handler_High))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        RB6_Interrupt_Handler_Low = Interrupt_Handler_Low;
        RB6_Interrupt_Handler_High = Interrupt_Handler_High;
    }
    
    return ret_state;
}

static Std_ReturnType Ext_Interrupt_RB7_SETHandler(void (* Interrupt_Handler_Low) (void) , void (* Interrupt_Handler_High) (void))
{
    Std_ReturnType ret_state = Func_Not_OK;
    if((NULL == Interrupt_Handler_Low) || (NULL == Interrupt_Handler_High))
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        RB7_Interrupt_Handler_Low = Interrupt_Handler_Low;
        RB7_Interrupt_Handler_High = Interrupt_Handler_High;
    }
    
    return ret_state;
}


static Std_ReturnType Ext_Interrupt_RBx_SETHandler(const EXTInterrupt_PBx_Type* Int_Obj)
{
    Std_ReturnType ret_state = Func_Not_OK;
    if(NULL == Int_Obj)
    {
        ret_state = Func_Not_OK;
    }
    else
    {
        switch(Int_Obj->Interrupt_Pins.Pin)
        {
            case GPIO_PIN4 :
            {
                ret_state = Ext_Interrupt_RB4_SETHandler(Int_Obj->Interrupt_Handler_LOW , Int_Obj->Interrupt_Handler_HIGH);
                break;
            }
            case GPIO_PIN5 :
            {
                ret_state = Ext_Interrupt_RB5_SETHandler(Int_Obj->Interrupt_Handler_LOW , Int_Obj->Interrupt_Handler_HIGH);
                break;
            }
            case GPIO_PIN6 :
            {
                ret_state = Ext_Interrupt_RB6_SETHandler(Int_Obj->Interrupt_Handler_LOW , Int_Obj->Interrupt_Handler_HIGH);
                break;
            }
            case GPIO_PIN7 :
            {
                ret_state = Ext_Interrupt_RB7_SETHandler(Int_Obj->Interrupt_Handler_LOW , Int_Obj->Interrupt_Handler_HIGH);
                break;
            }
            default : 
            {
                ret_state = Func_Not_OK;
            }
                
        }
    }
    
    return ret_state;
}

/*************************************************************/
