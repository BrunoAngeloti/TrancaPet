import { useEffect } from 'react';
import socket from '../../services/socketio';
import Swal from 'sweetalert2'

export function StatusSocketIO(){

    useEffect(() => {
        socket.on('status', (info) => {
            console.log(info)
            if (info === "ok") { 
                const Toast = Swal.mixin({
                  toast: true,
                  position: 'top-end',
                  showConfirmButton: false,
                  timer: 3000,
                  timerProgressBar: true,
                  didOpen: (toast) => {
                    toast.addEventListener('mouseenter', Swal.stopTimer)
                    toast.addEventListener('mouseleave', Swal.resumeTimer)
                  }
                })                    
                Toast.fire({
                  icon: 'success',
                  title: `Feito com sucesso`
                })                
            } 
            else {
                Swal.fire({
                    toast: true,
                    position: 'top-end',
                    showConfirmButton: false,
                    timer: 3000,
                    timerProgressBar: true,
                    didOpen: (toast) => {
                        toast.addEventListener('mouseenter', Swal.stopTimer)
                        toast.addEventListener('mouseleave', Swal.resumeTimer)
                    },
                    icon: 'error',
                    title: `${info}`
                })
            } 
        })

    },[])

    return (
        <div></div>
    )
}