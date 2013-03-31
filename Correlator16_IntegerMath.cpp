void Receiver::RunCorrelator16(int &maxcorrel, int &maxidx, bool &polarity)
{                                                                           
    maxcorrel = 0;                                                          
    maxidx    = 0;                                                          
    polarity  = false;                                                      

    int *ptr0 = &_rxseq[0];                  
    int *ptr1 = &_rxseq[8];                  
    int correl;                              

    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=0;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-0; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=1;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-1; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=2;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-2; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=3;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-3; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=4;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-4; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=5;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-5; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=6;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-6; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=7;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-7; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       neg ebx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=8;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-8; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       neg ebx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=9;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-9; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       neg ebx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=10;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-10; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       neg ebx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=11;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-11; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       neg ebx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=12;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-12; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       neg ebx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=13;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-13; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       neg ebx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=14;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-14; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       neg ebx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=15;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-15; }
    if(maxidx<0) { maxidx=-maxidx; polarity=true; }
}
