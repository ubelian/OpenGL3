#pragma once

/****************************************** 
****Заголовочный файл нужен для определения 
********директив включающих или отключающих 
*************************Функционал отладки
******************************************/

#define OGLRENDERER

#ifdef OGLRENDERER

#define VBO_DEBUG
#define SHADER_DEBUG
#define MVPMATRIX_DEBUG
//#define OGLOBJECT_DEBUG
#define OGLRENDERER_DEBUG


#endif //OGLRENDERER