void Receiver::RunCorrelator64(int &maxcorrel, int &maxidx, bool &polarity)
{                                                                           
    maxcorrel = 0;                                                          
    maxidx    = 0;                                                          
    polarity  = false;                                                      

    int *ptr0 = &_rxseq[0];                  
    int *ptr1 = &_rxseq[32];                 
    int correl;                              

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
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
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
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
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
       neg ebx
       add ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
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
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
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
       neg ebx
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
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
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
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
       neg ebx
       add ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
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
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
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
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
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
       add ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
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
       add ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
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
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
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
       sub ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
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
       add ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
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
       add ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=15;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-15; }
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
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=16;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-16; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=17;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-17; }
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
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=18;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-18; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=19;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-19; }
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
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=20;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-20; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=21;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-21; }
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
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=22;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-22; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=23;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-23; }
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
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=24;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-24; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=25;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-25; }
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
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=26;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-26; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=27;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-27; }
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
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=28;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-28; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=29;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-29; }
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
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=30;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-30; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=31;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-31; }
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
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=32;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-32; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=33;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-33; }
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
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=34;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-34; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=35;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-35; }
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
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=36;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-36; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=37;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-37; }
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
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=38;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-38; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=39;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-39; }
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
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=40;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-40; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=41;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-41; }
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
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=42;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-42; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=43;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-43; }
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
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=44;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-44; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=45;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-45; }
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
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=46;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-46; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=47;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-47; }
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
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=48;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-48; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=49;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-49; }
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
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=50;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-50; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=51;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-51; }
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
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=52;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-52; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=53;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-53; }
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
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=54;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-54; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=55;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-55; }
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
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=56;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-56; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=57;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-57; }
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
       add ebx, [edx+4]
       sub ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=58;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-58; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=59;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-59; }
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
       sub ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=60;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-60; }
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
       add ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=61;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-61; }
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
       add ebx, [edx+4]
       add ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=62;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-62; }
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
       sub ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=63;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-63; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=64;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-64; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=65;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-65; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=66;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-66; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=67;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-67; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=68;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-68; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=69;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-69; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=70;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-70; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=71;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-71; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=72;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-72; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=73;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-73; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=74;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-74; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=75;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-75; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=76;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-76; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=77;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-77; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=78;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-78; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=79;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-79; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=80;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-80; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=81;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-81; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=82;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-82; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=83;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-83; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=84;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-84; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=85;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-85; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=86;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-86; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=87;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-87; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=88;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-88; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=89;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-89; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=90;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-90; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=91;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-91; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=92;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-92; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=93;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-93; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=94;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-94; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       sub ecx, [eax+64]
       add ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=95;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-95; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=96;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-96; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=97;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-97; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=98;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-98; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=99;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-99; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=100;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-100; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=101;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-101; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=102;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-102; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=103;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-103; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=104;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-104; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=105;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-105; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=106;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-106; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=107;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-107; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=108;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-108; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=109;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-109; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=110;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-110; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=111;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-111; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=112;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-112; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=113;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-113; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=114;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-114; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=115;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-115; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=116;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-116; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=117;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-117; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=118;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-118; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       sub ecx, [eax+16]
       add ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       add ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       sub ecx, [eax+80]
       sub ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       sub ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=119;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-119; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=120;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-120; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=121;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-121; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       sub ecx, [eax+8]
       sub ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       sub ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=122;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-122; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       sub ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       sub ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       add ecx, [eax+88]
       add ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       add ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=123;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-123; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       sub ecx, [eax+4]
       add ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       add ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       sub ecx, [eax+28]
       sub ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       add ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       add ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       sub ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       add ecx, [eax+100]
       sub ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       add ecx, [eax+108]
       add ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=124;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-124; }
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
       add ecx, [eax+12]
       sub ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       sub ecx, [eax+20]
       sub ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       sub ecx, [eax+28]
       add ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       sub ecx, [eax+36]
       sub ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       sub ecx, [eax+44]
       sub ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       add ecx, [eax+76]
       sub ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       sub ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       add ecx, [eax+100]
       add ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       sub ecx, [eax+108]
       add ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       sub ecx, [eax+116]
       add ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       add ecx, [eax+124]
       add ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=125;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-125; }
    asm                                     
    {                                       
       push bx                              
                                            
       mov eax, ptr0                        
       mov edx, ptr1                        
                                            
       mov ecx, [eax]                       
       mov ebx, [edx]                       
                                            
       neg ecx
       add ecx, [eax+4]
       sub ebx, [edx+4]
       add ecx, [eax+8]
       add ebx, [edx+8]
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       sub ebx, [edx+20]
       sub ecx, [eax+24]
       add ebx, [edx+24]
       add ecx, [eax+28]
       add ebx, [edx+28]
       add ecx, [eax+32]
       add ebx, [edx+32]
       sub ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       sub ebx, [edx+40]
       sub ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       sub ebx, [edx+48]
       add ecx, [eax+52]
       sub ebx, [edx+52]
       add ecx, [eax+56]
       add ebx, [edx+56]
       add ecx, [eax+60]
       sub ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       add ecx, [eax+68]
       add ebx, [edx+68]
       sub ecx, [eax+72]
       sub ebx, [edx+72]
       add ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       sub ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       add ecx, [eax+92]
       sub ebx, [edx+92]
       sub ecx, [eax+96]
       add ebx, [edx+96]
       sub ecx, [eax+100]
       add ebx, [edx+100]
       add ecx, [eax+104]
       add ebx, [edx+104]
       sub ecx, [eax+108]
       sub ebx, [edx+108]
       add ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       add ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=126;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-126; }
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
       sub ecx, [eax+12]
       add ebx, [edx+12]
       add ecx, [eax+16]
       sub ebx, [edx+16]
       add ecx, [eax+20]
       add ebx, [edx+20]
       add ecx, [eax+24]
       sub ebx, [edx+24]
       add ecx, [eax+28]
       sub ebx, [edx+28]
       sub ecx, [eax+32]
       sub ebx, [edx+32]
       add ecx, [eax+36]
       add ebx, [edx+36]
       add ecx, [eax+40]
       add ebx, [edx+40]
       add ecx, [eax+44]
       add ebx, [edx+44]
       sub ecx, [eax+48]
       add ebx, [edx+48]
       sub ecx, [eax+52]
       add ebx, [edx+52]
       sub ecx, [eax+56]
       add ebx, [edx+56]
       sub ecx, [eax+60]
       add ebx, [edx+60]
       add ecx, [eax+64]
       sub ebx, [edx+64]
       sub ecx, [eax+68]
       sub ebx, [edx+68]
       add ecx, [eax+72]
       add ebx, [edx+72]
       sub ecx, [eax+76]
       add ebx, [edx+76]
       add ecx, [eax+80]
       add ebx, [edx+80]
       add ecx, [eax+84]
       add ebx, [edx+84]
       sub ecx, [eax+88]
       sub ebx, [edx+88]
       sub ecx, [eax+92]
       add ebx, [edx+92]
       add ecx, [eax+96]
       sub ebx, [edx+96]
       sub ecx, [eax+100]
       sub ebx, [edx+100]
       sub ecx, [eax+104]
       sub ebx, [edx+104]
       add ecx, [eax+108]
       sub ebx, [edx+108]
       sub ecx, [eax+112]
       add ebx, [edx+112]
       add ecx, [eax+116]
       sub ebx, [edx+116]
       sub ecx, [eax+120]
       sub ebx, [edx+120]
       sub ecx, [eax+124]
       sub ebx, [edx+124]
    
       mov  correl, ecx  
       add  correl, ebx  
       pop  bx           
    }                              

    if(correl>maxcorrel)  { maxcorrel =  correl; maxidx=127;  }
    if(correl<-maxcorrel) { maxcorrel = -correl; maxidx=-127; }
    if(maxidx<0) { maxidx=-maxidx; polarity=true; }
}

